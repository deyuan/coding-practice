// MT accumulate
// Copyright (c) 2021 Deyuan Guo <guodeyuan@gmail.com>. All rights reserved.

#include <vector>
#include <numeric>
#include <thread>
#include <iostream>
#include <sstream>
#include <chrono>

template<typename Iterator, typename T>
struct accumulate_block {
  void operator()(Iterator first, Iterator last, T& result) {
    // std::thread::id tid = std::this_thread::get_id();
    // std::stringstream ss;
    // ss << "Thread " << tid << " works on " << (last - first) << " data." << std::endl;
    // std::cout << ss.str();
    result = std::accumulate(first, last, result);
  }
};

template<typename Iterator, typename T>
T mt_accumulate(Iterator first, Iterator last, T init) {
  size_t len = last - first;
  if (!len) {
    return init;
  }

  // determine num threads and block size
  int min_block_size = 10;
  int max_num_blocks = (len + min_block_size - 1) / min_block_size;
  int thc = std::thread::hardware_concurrency();
  int num_threads = std::min((thc > 0 ? thc : 2), max_num_blocks);
  int block_size = len / num_threads;
  // std::cout << "INFO: num threads = " << num_threads << std::endl;
  // std::cout << "INFO: block size = " << block_size << std::endl;

  // create n-1 threads
  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);
  Iterator block_start = first;
  for (int i = 0; i < num_threads - 1; i++) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(accumulate_block<Iterator, T>(),
          block_start, block_end, std::ref(results[i]));  // std::ref
    block_start = block_end;
  }

  // main threads do the last part
  accumulate_block<Iterator, T>()(block_start, last, std::ref(results[num_threads - 1]));

  // join all threads
  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

  return std::accumulate(results.begin(), results.end(), init);
}

int main() {
  int thc = std::thread::hardware_concurrency();
  std::cout << "INFO: hardware concurrency = " << thc << std::endl;

  std::vector<int> data(1000000000, 1);

  for (int i = 0; i < 5; i++) {
    std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
    int sum1 = mt_accumulate<std::vector<int>::iterator, int>(data.begin(), data.end(), 0);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
    std::cout << "SUM = " << sum1 << std::endl;
    std::cout << "MT runtime = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count()
              << " ms" << std::endl;
  }

  for (int i = 0; i < 5; i++) {
    std::chrono::steady_clock::time_point start2 = std::chrono::steady_clock::now();
    int sum2 = std::accumulate(data.begin(), data.end(), 0);
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    std::cout << "SUM = " << sum2 << std::endl;
    std::cout << "STL runtime = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count()
              << " ms" << std::endl;
  }
}
