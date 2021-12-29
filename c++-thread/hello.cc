// A simple example of thread creation and join
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <thread>

void task() {
  // outputs from different threads can interleave
  std::cout << "This " << "is " << "a " << "test " << std::endl;
}

int main() {
  int numThreads = std::thread::hardware_concurrency();
  std::cout << "Number of threads: " << numThreads << std::endl;

  // create threads
  std::vector<std::thread> threads;
  for (int i = 0; i < numThreads; ++i) {
    threads.emplace_back(std::thread(task));
  }

  // join threads
  for (auto &t : threads) {
    t.join();
  }
}
