// An example of promise and future
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>
#include <future>

void task1(std::promise<int>& p_notice) {
  std::cout << "Task1 sends a one-off notice" << std::endl;
  p_notice.set_value(123);
}

void task2(std::future<int>& f_notice) {
  int notice = f_notice.get();
  std::cout << "Task2 gets the one-off notice " << notice << std::endl;
}

int main() {
  std::promise<int> p_notice;
  std::future<int> f_notice = p_notice.get_future();

  std::thread t1(task1, std::ref(p_notice));
  std::thread t2(task2, std::ref(f_notice));

  t1.join();
  t2.join();
}
