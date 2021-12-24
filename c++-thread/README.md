# C++ Thread

## Readings
* C++ Concurrency in Action, Second Edition

## Notes
* Compiler flags
  * `-std=c++11`, `-std=c++14`, `-std=c++17`
* Thread STL
  * Header file
    * `#include <thread>`
  * Simple thread
    * `void task();`
    * `std::thread t(task);`
    * Thread is movable but not copyable
  * Vector of threads
    * `std::vector<std::thread> threads;`
    * `threads.emplace_back(std::thread(task));`
  * Callable
    * Global function, function pointer
    * Member function
    * Callable object
    * Lambda function
  * Detach or join
    * `t.detach()`
      * Then `t.joinable()` will be false
      * Daemon thread
      * Example: word processor UI
    * `t.join()`
      * Can be called once, then `t.joinable()` will be false
    * Don't skip join when an exception occurs
      * Need two `join()` in and after the `catch` block
      * Or use a thread_guard RAII class
  * Arguments to threads
    * Pass by copy by default
    * Use `std::ref()` to force to pass as reference
    * `std::mem_fn` as a wrapper of a member function
  * Thread ID
    * `std::this_thread::get_id()`
  * Hardware concurrency
    * `std::thread::hardware_concurrency()`
  * Measure runtime
    * `#include <chrono>`
    * `std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();`
    * `std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n"`
* Data sharing
  * Lock-free programming
  * Software transactional memory (STM)
  * mutex
    * `#include <mutex>`
    * `std::mutex m;`
    * `std::lock_guard<std::mutex> l(m);`
  * Don't pass pointers or references outside of the lock scope
    * E.g. user-supplied function
  * Eliminate race condition, e.g. stack pop() vs. top()
    * Pass in a reference
    * Require a no-throw copy constructor or move constructor
    * Return a pointer to the popped item
    * Provide both option 1 and either option 2 or 3
  * Dead lock
    * Examples
      * Two mutex locked in different order
      * Two threads call join() of each other
      * Nested locks, locks from user-supplied data structure or functions
    * Solutions
      * Lock mutex in order
      * `std::lock()` can lock multiple mutex at once
      * `hierarchical_mutex`
      * `std::unique_lock`
      * `std::adopt_lock`
      * `std::defer_lock`
* Condition variable and future
  * `std::condition_variable cv;`
  * `cv.notify_one();`
  * `cv.notify_all();`
  * `cv.wait(lock, [](){ return cond; });`
    * Unique lock is required
    * Same as while (cond) wait
  * One-off event (happen only once)
    * `std::async`
    * `std::future`
    * `std::shared_future`
  * Alternative
    * `std::packaged_task`
    * `std::promise`
  * Duration and timeout
    * sleep_for/wait_for duration
    * sleep_until/wait_until time_point
* Dining Philosophers Problem
  * Solutions
    * Arbitrator solution
      * Allow to pick two or none
    * Resource hierarchy solution
      * Last or even people pick left first, others pick right first
    * Limiting #diners
      * Allow at most n-1
    * Chandy/Misra solution
      * This prevents starvation
      * https://mariusbancila.ro/blog/2017/01/20/dining-philosophers-in-c11-chandy-misra-algorithm/


