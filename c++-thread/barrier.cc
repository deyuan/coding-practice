// Implemente a thread barrier using condition variable
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

// A reusable barrier
// The key is to differentiate back-to-back barrier wait
class Barrier {
 public:
  explicit Barrier(int numThreads) : numThreads_(numThreads), count_(0) {}
  ~Barrier() {}

  void wait() {
    std::unique_lock<std::mutex> lock(mut_);
    // Enter phase
    // When all threads are waiting, the counter will reach numThreads_
    // and trigger notify_all, so that all threads can proceed.
    // But, the wait statement may be overlapped with exit phase of
    // other threads, so >= operation is used to avoid dead lock.
    count_ = (count_ + 1) % (2 * numThreads_);
    cv_.wait(lock, [this](){ return count_ >= numThreads_; });
    if (count_ == numThreads_) {
      cv_.notify_all();
    }
    // Exit phase
    // When all threads are waiting, the counter will reach 0 and trigger
    // notify_all, so that all threads can proceed.
    // But, the wait statement may be overlapped with enter phase of
    // other threads, so < operation is used to avoid dead lock.
    count_ = (count_ + 1) % (2 * numThreads_);
    cv_.wait(lock, [this](){ return count_ < numThreads_; });
    if (count_ == 0) {
      cv_.notify_all();
    }
  }

 private:
  int numThreads_;
  std::atomic<int> count_;
  std::mutex mut_;
  std::condition_variable cv_;
};

// Mutex for output
std::mutex iomut;

// Thread task
void task(int id, Barrier& barrier) {
  std::unique_lock<std::mutex> iolock(iomut, std::defer_lock);
  for (int i = 0; i < 5; i++) {
    iolock.lock();
    std::cout << "Thread " << id << " is at step " << i << std::endl;
    iolock.unlock();
    // thread barrier
    barrier.wait();
  }
}

int main() {
  int numThreads = std::thread::hardware_concurrency();

  Barrier barrier(numThreads);

  std::vector<std::thread> threads;
  for (int i = 0; i < numThreads; i++) {
    threads.emplace_back(task, i, std::ref(barrier));
  }

  for (auto &t : threads) {
    t.join();
  }
}
