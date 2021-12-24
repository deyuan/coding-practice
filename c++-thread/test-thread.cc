// Copyright (c) 2018 Deyuan Guo. All rights reserved.
// This file is subject to the terms and conditions defined
// in file 'LICENSE' in this source code package.

#include <iostream>
#include <thread>
#include <string>
#include <sstream>    // stringstream
#include <chrono>     // system_clock, duration, seconds

// Note: Compiler flag -std=c++11 is needed for using <thread>
// <thread> includes std::thread class and std::this_thread namespace

// A function-pointer-based thread worker with simple primitive parameters
void Worker1(std::string name, int nIter) {
  for (int i = 0; i < nIter; i++) {
    // Note: Cannot add std::endl to string, since std::endl = "\n" + flush()
    // Note: Cannot use std::to_string() to convert thread id to string
    // Note: std::cout is thread-safe, however multiple << may interleave
    std::thread::id tid = std::this_thread::get_id();
    std::stringstream ss;  // sstream
    ss << "  TID " << tid << " Name " << name << " Iter " << i << std::endl;
    std::cout << ss.str();
  }
}

void MtStdThread() {
  // Note: Test thread::id, this_thread::get_id() and hardware_concurrency
  std::thread::id mainTid = std::this_thread::get_id();
  std::cout << "Main thread id is " << mainTid << std::endl;
  unsigned hwConcurrency = std::thread::hardware_concurrency();
  std::cout << "Hardware concurrency is " << hwConcurrency << std::endl;

  ////////////////////////////////////////////////////////////////////////////
  // Note: Test thread creation, parameter passing, swap, move, join/joinable
  // After swap or move, thread will continue executing with the same thread id
  // join() - block until thread has completed
  std::cout << "\nTesting worker 1 ..." << std::endl;

  std::thread t1(Worker1, "t1 (test)", 5);
  std::thread t2(Worker1, "t2 (test-detach)", 5);
  std::thread t3(Worker1, "t3 (test-swap-move)", 20);

  t2.detach();  // Test std::thread::detach - detach t2 from main thread
  std::cout << "Detach thread t2\n";

  // t1 is joinable, and main thread will wait at join() until t1 finishes
  if (t1.joinable()) {
    t1.join();
    std::cout << "Thread t1 is finished\n";
  } else {
    std::cout << "Thread t1 is not joinable\n";
  }

  // t2 is not joinable because it is detached
  if (t2.joinable()) {
    t2.join();
    std::cout << "Thread t2 is finished\n";
  } else {
    std::cout << "Thread t2 is not joinable\n";
  }

  std::thread t3s;
  t3s.swap(t3);  // Test std::thread::swap
  std::cout << "Swap thread t3 with t3-swap\n";

  // t3 is not joinable because the running thread is swapped to t3s
  if (t3.joinable()) {
    t3.join();
    std::cout << "Thread t3 is finished\n";
  } else {
    std::cout << "Thread t3 is not joinable\n";
  }

  // Thread is not copyable. std::move() is needed to do a move-assign
  std::thread t3m = std::move(t3s);  // Test move-assign
  std::cout << "Move thread t3-swap to t3-move\n";

  // t3s is not joinable because the running thread is moved to t3m
  if (t3s.joinable()) {
    t3s.join();
    std::cout << "Thread t3-swap is finished\n";
  } else {
    std::cout << "Thread t3-swap is not joinable\n";
  }

  // t3m is joinable, and main thread will wait at join()
  if (t3m.joinable()) {
    t3m.join();
    std::cout << "Thread t3-move is finished\n";
  } else {
    std::cout << "Thread t3-move is not joinable\n";
  }

  ////////////////////////////////////////////////////////////////////////////
  // Note: Test yield, sleep_for and sleep_until in this_thread NS
  std::cout << "\nTest this_thread ..." << std::endl;

  // Calling yield() can trigger rescheduling and give other threads priority
  std::this_thread::yield();  // no-op

  // Test sleep_for()
  for (int i = 0; i < 3; ++i) {
    std::cout << "Main thread sleep for 1 second" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // Test sleep_until()
  std::cout << "Main thread sleep until 5 seconds from now" << std::endl;
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::chrono::duration<int, std::ratio<1, 1>> delta(5);  // 5 seconds
  std::this_thread::sleep_until(now + delta);
  std::cout << "Done!" << std::endl;
}

int main() {
  MtStdThread();
  return 0;
}


