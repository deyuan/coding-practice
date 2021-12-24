// An example of paskaged_task
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>
#include <future>
#include <queue>

std::mutex mut;
bool isDone = false;
std::queue<std::packaged_task<void()>> tasks;

void my_worker_thread() {
  while (!isDone) {
    std::packaged_task<void()> task;
    {
      std::lock_guard<std::mutex> lock(mut);
      if (tasks.empty()) {
        continue;
      }
      task = std::move(tasks.front());
      tasks.pop();
    }
    task();
  }
}

template<typename Func>
std::future<void> submit_task(Func f) {
  std::packaged_task<void()> task(f);
  std::future<void> res = task.get_future();
  std::lock_guard<std::mutex> lock(mut);
  tasks.push(std::move(task));
  return res;
}

void task1() {
  std::cout << "task1" << std::endl;
}

void task2() {
  std::cout << "task2" << std::endl;
}

void task3() {
  std::cout << "task3" << std::endl;
}

int main() {
  std::thread worker(my_worker_thread);
  std::future<void> f1 = submit_task(task1);
  std::future<void> f2 = submit_task(task2);
  std::future<void> f3 = submit_task(task3);
  f1.wait();
  f2.wait();
  f3.wait();
  isDone = true;
  worker.join();
}
