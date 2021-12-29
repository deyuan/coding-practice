// Test Semaphore: Running Game
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <thread>
#include <semaphore.h>
#include <chrono>

sem_t *sem = nullptr;
int rank = -100;

void student(int id) {
  sem_wait(sem);
  rank++;
  std::cout << "Student " << id << ": rank " << rank << std::endl;
  sem_post(sem);
}

void teacher() {
  std::cout << "Teacher: Ready in 3 seconds..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  std::cout << "Teacher: Go!" << std::endl;
  rank = 0;
  sem_post(sem);
}

int main() {
  const char* name = "/mysem";
  sem = sem_open(name, O_CREAT, S_IRUSR|S_IWUSR, 0);

  std::thread tt(teacher);
  std::vector<std::thread> threads;
  for (int i = 1; i <= 5; i++) {
    threads.emplace_back(student, i);
  }

  tt.join();
  for (auto& t : threads) {
    t.join();
  }

  sem_close(sem);
  sem_unlink(name);
  sem = nullptr;
}
