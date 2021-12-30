// Solution to the Cigarette Smoker Problem
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

std::mutex mut_agent;
std::condition_variable cv_agent;
bool has_tobacco = false;
bool has_paper = false;
bool has_match = false;
bool done_smoking = false;
bool is_done = false;

void agent() {
  std::unique_lock<std::mutex> lock_agent(mut_agent);
  for (int i = 0; i < 10; i++) {
    std::cout << "Agent: Round " << i << ": ";
    done_smoking = false;
    int val = rand() % 3;
    if (val == 0) {
      std::cout << "Put tobacco and paper on the table" << std::endl;
      has_tobacco = has_paper = true;
    } else if (val == 1) {
      std::cout << "Put paper and match on the table" << std::endl;
      has_paper = has_match = true;
    } else {
      std::cout << "Put match and tobacco on the table" << std::endl;
      has_match = has_tobacco = true;
    }
    cv_agent.notify_all();
    cv_agent.wait(lock_agent, [](){ return done_smoking; });
  }
  is_done = true;
  cv_agent.notify_all();
}

void tobacco_smoker() {
  while (true) {
    std::unique_lock<std::mutex> lock_agent(mut_agent);
    cv_agent.wait(lock_agent, [](){ return (has_paper && has_match) || is_done; });
    if (is_done) { break; }
    has_paper = false;
    has_match = false;
    std::cout << "Tobacco smoker: Smoking..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    done_smoking = true;
    cv_agent.notify_all();
  }
}

void paper_smoker() {
  while (true) {
    std::unique_lock<std::mutex> lock_agent(mut_agent);
    cv_agent.wait(lock_agent, [](){ return (has_tobacco && has_match) || is_done; });
    if (is_done) { break; }
    has_tobacco = false;
    has_match = false;
    std::cout << "Paper smoker: Smoking..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    done_smoking = true;
    cv_agent.notify_all();
  }
}

void match_smoker() {
  while (true) {
    std::unique_lock<std::mutex> lock_agent(mut_agent);
    cv_agent.wait(lock_agent, [](){ return (has_tobacco && has_paper) || is_done; });
    if (is_done) { break; }
    has_tobacco = false;
    has_paper = false;
    std::cout << "Match smoker: Smoking..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    done_smoking = true;
    cv_agent.notify_all();
  }
}

int main() {
  std::srand(std::time(nullptr));
  std::vector<std::thread> threads;
  threads.emplace_back(agent);
  threads.emplace_back(tobacco_smoker);
  threads.emplace_back(paper_smoker);
  threads.emplace_back(match_smoker);
  for (auto &t : threads) {
    t.join();
  }
}
