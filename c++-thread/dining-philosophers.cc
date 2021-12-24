// Dining Philosophers
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>

const int numPhilosophers = 10;
const int numEats = 10;
std::vector<std::mutex> muts(numPhilosophers);

// Resource hierarchy solution to prevent dead lock
void wantToEat(int philosopher) {
  int idx1 = philosopher;
  int idx2 = (philosopher + 1) % numPhilosophers;
  if (philosopher % 2 == 0) {
    std::swap(idx1, idx2);  // even number left handness
  }
  std::lock_guard<std::mutex> lock1(muts[idx1]);
  std::lock_guard<std::mutex> lock2(muts[idx2]);

  std::stringstream ss;
  ss << "Philosopher " << philosopher << " eats with forks " << idx1 << " and " << idx2 << std::endl;
  std::cout << ss.str();
}

void task(int philosopher) {
  for (int i = 0; i < numEats; i++) {
    wantToEat(philosopher);
  }
}

int main() {
  std::vector<std::thread> threads;
  for (int i = 0; i < numPhilosophers; ++i) {
    threads.emplace_back(std::thread(task, i));
  }
  for (auto &t : threads) {
    t.join();
  }
}
