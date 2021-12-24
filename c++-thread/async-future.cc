// Examples of async and future
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <future>
#include <iostream>

int async_task1() {
  return 1;
}

int async_task2() {
  return 2;
}

class MyClass {
 public:
  MyClass() : val_(3) {}
  int async_task3() { return val_; }
 private:
  int val_;
};

int main() {
  std::future<int> f1 = std::async(async_task1);
  std::future<int> f2 = std::async(std::launch::deferred, async_task2);
  MyClass obj;
  std::future<int> f3 = std::async(std::launch::async, &MyClass::async_task3, &obj);
  std::cout << f1.get() << std::endl;
  std::cout << f2.get() << std::endl;
  std::cout << f3.get() << std::endl;
}
