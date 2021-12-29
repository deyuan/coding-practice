// ABA problem
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> shared_val1 = 0;
std::atomic<int> shared_val2 = 0;

void task_good() {
  for (int i = 0; i < 10000; i++) {
    // c++ atomic ++ or += is good
    shared_val1++;
  }
}

void task_bad() {
  for (int i = 0; i < 10000; i++) {
    // there is a delta time between read and write,
    // which may interleave with another thread
    shared_val2 = shared_val2 + 1;
  }
}


int main() {
  std::thread t1(task_good);
  std::thread t2(task_good);
  t1.join();
  t2.join();
  std::cout << "Good result: " << shared_val1 << std::endl;

  std::thread t3(task_bad);
  std::thread t4(task_bad);
  t3.join();
  t4.join();
  std::cout << "Bad result:  " << shared_val2 << std::endl;
}
