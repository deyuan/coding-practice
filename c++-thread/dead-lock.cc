// Examples of dead lock
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

std::mutex m1;
std::mutex m2;

void task1_bad() {
  std::lock_guard<std::mutex> lock1(m1);
  std::cout << "t1: lock m1\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::lock_guard<std::mutex> lock2(m2);
  std::cout << "t1: lock m2\n";
}

void task2_bad() {
  std::lock_guard<std::mutex> lock1(m2);
  std::cout << "t2: lock m2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::lock_guard<std::mutex> lock2(m1);
  std::cout << "t2: lock m1\n";
}

void task1_good1() {
  std::lock(m1, m2);
  std::cout << "t1: lock m1, m2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::lock_guard<std::mutex> lock1(m1, std::adopt_lock);
  std::cout << "t1: lock guard adopt m1\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::lock_guard<std::mutex> lock2(m2, std::adopt_lock);
  std::cout << "t1: lock guard adopt m2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void task2_good1() {
  std::lock(m2, m1);
  std::cout << "t2: lock m2, m1\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::lock_guard<std::mutex> lock1(m2, std::adopt_lock);
  std::cout << "t2: lock guard adopt m2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::lock_guard<std::mutex> lock2(m1, std::adopt_lock);
  std::cout << "t2: lock guard adopt m1\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void task1_good2() {
  std::unique_lock<std::mutex> lock1(m1, std::defer_lock);
  std::cout << "t1: unique lock hold m1\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::unique_lock<std::mutex> lock2(m2, std::defer_lock);
  std::cout << "t1: unique lock hold m2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  // std::lock(m1, m2);  // bad
  std::lock(lock1, lock2);
  std::cout << "t1: lock lock1, lock2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void task2_good2() {
  std::unique_lock<std::mutex> lock1(m2, std::defer_lock);
  std::cout << "t2: unique lock hold m2\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::unique_lock<std::mutex> lock2(m1, std::defer_lock);
  std::cout << "t2: unique lock hold m1\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  // std::lock(m2, m1);  // bad
  std::lock(lock2, lock1);
  std::cout << "t2: lock lock2, lock1\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main() {
  if (0) {
    std::thread t1(task1_bad);
    std::thread t2(task2_bad);
    t1.join();
    t2.join();
    std::cout << "--------\n";
  }
  if (1) {
    std::thread t1(task1_good1);
    std::thread t2(task2_good1);
    t1.join();
    t2.join();
    std::cout << "--------\n";
  }
  if (1) {
    std::thread t1(task1_good2);
    std::thread t2(task2_good2);
    t1.join();
    t2.join();
    std::cout << "--------\n";
  }
}
