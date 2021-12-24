// Examples of condition variable
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

std::mutex mut;
std::condition_variable cv;
std::vector<int> data;
bool isReady = false;
bool isDone = false;

void producer() {
  // use lock_guard to produce data
  std::lock_guard<std::mutex> lock(mut);
  for (int i = 0; i < 100; i++) {
    data.push_back(i);
  }
  isReady = true;
  // notify one thread to process
  cv.notify_one();
}

void consumer(int id) {
  // condition_variable requires unique_lock
  std::unique_lock<std::mutex> lock(mut);
  // wait for the condition to be true like a while loop
  cv.wait(lock, [](){ return isReady || isDone; });
  if (!isDone) {
    // the lucky thread
    std::cout << "Thread " << id << " get " << data.size() << " data" << std::endl;
    data.clear();
    isDone = true;
    cv.notify_all();  // notify remaining threads to stop
  } else {
    // the rest threads
    std::cout << "Thread " << id << " cannot get any data" << std::endl;
  }
}

int main() {
  std::thread t1(producer);
  std::thread t2(consumer, 1);
  std::thread t3(consumer, 2);
  std::thread t4(consumer, 3);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}
