// Implement a spinlock mutex using atomic
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

class SpinLock {
 public:
  SpinLock() : flag(ATOMIC_FLAG_INIT) {}
  void lock() {
    while (flag.test_and_set(std::memory_order_acquire));
  }
  void unlock() {
    flag.clear(std::memory_order_release);
  }
 private:
  std::atomic_flag flag;
};

class SpinLockBad {
 public:
  SpinLockBad() : flag(false) {}
  void lock() {
    while (flag);
    flag = true;
  }
  void unlock() {
    flag = false;
  }
 private:
  volatile bool flag;
};

SpinLock sl1;
SpinLockBad sl2;

void task(int n, int test) {
  for (int i = 0; i < 100; i++) {
    if (test) {
      sl1.lock();
      std::cout << n << " ";
      sl1.unlock();
    } else {
      sl2.lock();
      std::cout << n << " ";
      sl2.unlock();
    }
  }
}

int main() {
  for (int i = 0; i <= 1; i++) {
    std::cout << "Test " << i << std::endl;
    std::thread t1(task, 1, i);
    std::thread t2(task, 2, i);
    std::thread t3(task, 3, i);
    t1.join();
    t2.join();
    t3.join();
    std::cout << std::endl;
  }
}
