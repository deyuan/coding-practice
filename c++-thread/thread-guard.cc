// Examples of thread guard and scoped thread
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>

// ThreadGrard: Holds reference of a thread
class ThreadGuard {
 public:
  explicit ThreadGuard(std::thread &t) : t_(t) {
  }
  ~ThreadGuard() {
    if (t_.joinable()) {
      t_.join();
    }
  }
 private:
  std::thread &t_;
};

// ScopedThread: Take the ownership of a thread
class ScopedThread {
 public:
  explicit ScopedThread(std::thread t) : t_(std::move(t)) {
  }
  ~ScopedThread() {
    if (t_.joinable()) {
      t_.join();
    }
  }
 private:
  ScopedThread(ScopedThread const&) = delete;
  ScopedThread& operator=(ScopedThread const&) = delete;
  std::thread t_;
};

void task() {
  std::cout << "test thread guard and scoped thread\n";
}

int main() {
  std::thread t1(task);
  ThreadGuard g(t1);

  std::thread t2(task);
  ScopedThread st(std::move(t2));
}

