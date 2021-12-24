// A thread-safe queue
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <chrono>
#include <memory>

// Notes: Do not have separate front() and pop() to avoid race condition,
// since front() and pop() from diffenrent threads may interleave
template<typename T>
class ThreadsafeQueue {
 public:
  ThreadsafeQueue() {}
  ThreadsafeQueue(const ThreadsafeQueue& other) {
    std::lock_guard<std::mutex> lock(other.m_);  // need to lock the other mutex
    data_ = other.data_;
  }
  ThreadsafeQueue& operator=(const ThreadsafeQueue&) = delete;

  void push(T val) {
    std::lock_guard<std::mutex> lock(m_);
    data_.push(val);
    data_cond_.notify_one();
  }

  // return front, blocking
  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lock(m_);
    data_cond_.wait(lock, [this](){ return !data_.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_.front()));
    data_.pop();
    return res;
  }

  // return front, blocking
  void wait_and_pop(T& val) {
    std::unique_lock<std::mutex> lock(m_);
    data_cond_.wait(lock, [this](){ return !data_.empty(); });
    val = data_.front();
    data_.pop();
  }

  // return nullptr if there is no data, non-blocking
  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lock(m_);
    if (data_.empty()) {
      return std::make_shared<T>();
    }
    std::shared_ptr<T> res(std::make_shared<T>(data_.front()));
    data_.pop();
    return res;
  }

  // return false if there is no data, non-blocking
  bool try_pop(T& val) {
    std::lock_guard<std::mutex> lock(m_);
    if (data_.empty()) {
      return false;
    }
    val = data_.front();
    data_.pop();
    return true;
  }

  bool empty() const {
    // use lock_guard for data_ read
    std::lock_guard<std::mutex> lock(m_);
    return data_.empty();
  }

 private:
  std::queue<T> data_;
  mutable std::mutex m_;  // can be modified with const
  std::condition_variable data_cond_;
};


// testing thread
void task1(ThreadsafeQueue<int>& q, int tid) {
  // std::thread::id tid = std::this_thread::get_id();
  bool use_ref = true;
  for (int i = 0; i < 5; i++) {
    std::stringstream ss;
    int op = rand() % 2;
    if (op || tid == 0) {
      int val = rand() % 100;
      q.push(val);
      ss << "[T=" << i << "] Thread " << tid << " pushed " << val << std::endl;
    } else {
      int val = -1;
      if (use_ref) {
        q.wait_and_pop(val);  // this can hang if all remaining threads are waiting
      } else {
        std::shared_ptr<int> p = q.wait_and_pop();
        val = *p;
      }
      ss << "[T=" << i << "] Thread " << tid << " popped     " << val << std::endl;
    }
    std::cout << ss.str();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int main() {
  std::srand(std::time(nullptr));

  // int thc = std::thread::hardware_concurrency();
  // int numThreads = (thc > 0 ? thc : 2);
  int numThreads = 4;
  std::vector<std::thread> threads(numThreads);

  ThreadsafeQueue<int> q;

  for (int j = 0; j < numThreads; ++j) {
    threads[j] = std::thread(task1, std::ref(q), j);
  }

  std::for_each(threads.begin(), threads.end(),
      std::mem_fn(&std::thread::join));
}
