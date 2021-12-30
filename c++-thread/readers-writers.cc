// Solution to the Readers-writers Problem
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <semaphore.h>

int shared_data = 0;
int read_count = 0;

std::mutex mut_service;
std::mutex mut_readcnt;
std::mutex mut_io;
sem_t *sem_resource = nullptr;

void reader(int id) {
  for (int i = 0; i < 100; i++) {
    // service queue to avoid starvation
    std::unique_lock<std::mutex> lock_service(mut_service);
    std::unique_lock<std::mutex> lock_readcnt(mut_readcnt);
    read_count++;
    if (read_count == 1) {
      // use semaphore here because it may be acquired/released by different readers
      sem_wait(sem_resource);
    }
    lock_readcnt.unlock();
    lock_service.unlock();

    // critical section
    std::unique_lock<std::mutex> lock_io(mut_io);
    std::cout << "Reader " << id << " reads shared data as " << shared_data << std::endl;
    lock_io.unlock();

    // the last reader releases the resource
    lock_readcnt.lock();
    read_count--;
    if (read_count == 0) {
      sem_post(sem_resource);
    }
    lock_readcnt.unlock();
  }
}

void writer(int id) {
  for (int i = 0; i < 100; i++) {
    // service queue to avoid starvation
    std::unique_lock<std::mutex> lock_service(mut_service);
    sem_wait(sem_resource);
    lock_service.unlock();

    // critical section
    shared_data = id;
    std::lock_guard<std::mutex> lock_io(mut_io);
    std::cout << "Writer " << id << " updates shared data as " << shared_data << std::endl;
    sem_post(sem_resource);
  }
}

int main() {
  const char *name = "/mysemres";
  // Note: Explicitly unlink since the semaphore may not be closed
  // if previous run was terminated with ctrl-c
  sem_unlink(name);
  sem_resource = sem_open(name, O_CREAT, S_IRUSR|S_IWUSR, 1);

  std::thread tr1(reader, 1);
  std::thread tr2(reader, 2);
  std::thread tr3(reader, 3);
  std::thread tr4(reader, 4);
  std::thread tw1(writer, 1);
  std::thread tw2(writer, 2);

  tr1.join();
  tr2.join();
  tr3.join();
  tr4.join();
  tw1.join();
  tw2.join();

  sem_close(sem_resource);
  sem_unlink(name);
  sem_resource = nullptr;
}
