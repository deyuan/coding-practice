// Examples of callable objects that a thread can take
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>

void task1() {
  std::cout << "Task1 is a global function\n";
}

class Task2 {
 public:
  Task2() : count(0) {}
  void task() {
    std::cout << "Task2 is a member function\n";
    count++;
  }
  int count;
};

class Task3 {
 public:
  Task3() : count(0) {}
  void operator()() {
    std::cout << "Task3 is a callable object\n";
    count++;
  }
  int count;
};

int main() {
  // use a global function
  std::thread t1(task1);
  t1.join();

  // use a pointer to a global function
  void (*fp)() = &task1;
  std::thread t1a(fp);
  t1a.join();

  // use a class member function
  Task2 task2;
  std::thread t2(&Task2::task, &task2);  // pass member function and object
  t2.join();
  std::cout << task2.count << std::endl;  // expect 1

  // use a callable object
  Task3 task3;
  std::thread t3(task3);  // pass callable by copy
  t3.join();
  std::cout << task3.count << std::endl;  // expect 0
  std::thread t3a(std::ref(task3));  // pass callable by reference
  t3a.join();
  std::cout << task3.count << std::endl;  // expect 1
  std::thread t3b((Task3()));
  t3b.join();
  std::thread t3c{Task3()};
  t3c.join();
  // std::thread t3d(Task3());  // This declares a function

  // use lambda
  std::thread t4([](){ task1(); });
  t4.join();
  std::thread t4a([&task3](){ task3(); });  // pass callable by reference
  t4a.join();
  std::cout << task3.count << std::endl;  // expect 2
}
