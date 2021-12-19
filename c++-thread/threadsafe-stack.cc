// A thread-safe stack
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <mutex>
#include <thread>
#include <stack>
#include <exception>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <chrono>
#include <memory>

struct empty_stack : public std::exception {
  const char* what() const throw() {
    return "Stack is empty!";
  }
};

// Notes: Do not have separate top() and pop() to avoid race condition
// top() and pop() from diffenrent threads may interleave
template<typename T>
class ThreadsafeStack {
 public:
  ThreadsafeStack() {}
  ThreadsafeStack(const ThreadsafeStack& other) {
    std::lock_guard<std::mutex> lock(m_);
    data_ = other.data_;
  }
  ThreadsafeStack& operator=(const ThreadsafeStack&) = delete;

  void push(T val) {
    std::lock_guard<std::mutex> lock(m_);
    data_.push(val);
  }
  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m_);
    if (data_.empty()) {
      // may throw an exception here
      std::shared_ptr<T> const res(nullptr);
      return res;
    } else {
      std::shared_ptr<T> const res(std::make_shared<T>(data_.top()));
      data_.pop();
      return res;
    }
  }

  void pop(T& val) {
    std::lock_guard<std::mutex> lock(m_);
    if (data_.empty()) {
      // there is no data to assign to val
      throw empty_stack();
    } else {
      val = data_.top();
      data_.pop();
    }
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m_);
    return data_.empty();
  }

 private:
  std::stack<T> data_;
  mutable std::mutex m_;  // can be modified with const
};

void task1(ThreadsafeStack<int>& st, int tid) {
  // std::thread::id tid = std::this_thread::get_id();
  bool use_ref = true;
  for (int i = 0; i < 5; i++) {
    std::stringstream ss;
    int op = rand() % 2;
    if (op) {
      st.push(i);
      ss << "[" << i << "] Thread " << tid << " pushed " << i << std::endl;
    } else {
      int val = -1;
      if (use_ref) {
        try {
          st.pop(val);
        } catch (const std::exception& e) {
          val = -2;
        }
      } else {
        std::shared_ptr<int> p = st.pop();
        if (p) val = *p;
      }
      ss << "[" << i << "] Thread " << tid << " popped " << val << std::endl;
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

  ThreadsafeStack<int> st;

  for (int j = 0; j < numThreads; ++j) {
    threads[j] = std::thread(task1, std::ref(st), j);
  }

  std::for_each(threads.begin(), threads.end(),
      std::mem_fn(&std::thread::join));
}
