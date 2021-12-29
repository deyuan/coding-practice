# C++ Multi-threading

## Compiler
* Makefile
  * Compiler flags: `-std=c++11`, `-std=c++14`, `-std=c++17`

## Thread Basics
* `hello.cc` - Multi-threading hello world
  * Header: `#include <thread>`
  * Hardware concurrency: `std::thread::hardware_concurrency()`
  * Simple thread
    * `void task();`
    * `std::thread t(task);`
    * Thread is movable but not copyable
  * Vector of threads
    * `std::vector<std::thread> threads;`
    * `threads.emplace_back(std::thread(task));`
* `test-thread.cc` - Test thread basics
  * Detach or join
    * `t.detach()`
      * Then `t.joinable()` will be false
      * Daemon thread
      * Example: word processor UI
    * `t.join()`
      * Can be called once, then `t.joinable()` will be false
  * Duration and timeout
    * sleep_for/wait_for duration
    * sleep_until/wait_until time_point
* `callable.cc` - Callable tasks that can be passed to threads
  * Callable
    * Global function, function pointer
    * Member function
    * Callable object
      * Use `thread((task()))` or `thread{task()}`
      * Do not use `thread(task())` which is a function declaration
    * Lambda function
* `dead-lock.cc` - Test dead lock
  * Lock-free programming
  * Software transactional memory (STM)
  * mutex
    * `#include <mutex>`
    * `std::mutex m;`
    * `std::lock_guard<std::mutex> l(m);`
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
  * Don't pass pointers or references outside of the lock scope
    * E.g. user-supplied function
* `condition-variable.cc` - Test condition variable
  * `std::condition_variable cv;`
  * `cv.notify_one();`
  * `cv.notify_all();`
  * `cv.wait(lock, [](){ return cond; });`
    * Unique lock is required
    * Same as while (cond) wait
* `async-future.cc` - Test async and future
  * One-off event (happen only once)
    * `std::async`
    * `std::future`
    * `std::shared_future`
* `packaged-task.cc` - Test packaged task
  * `std::packaged_task`
  * `std::future`
* `promise.cc` - Test promise
  * `std::promise`
  * `std::future`

## Classic Problems
* `aba-problem.cc` - Demonstrate the ABA problem
  * ABA Problem: https://en.wikipedia.org/wiki/ABA_problem
  * Thread interleaving
  * C++ atomic data type
    * `#include <atomic>`
    * ++ and += are atomic
    * `val = val + 1` is not atomic
* `dining-philosophers.cc` - Solve the dining philosopher problem
  * Dining Philosophers Problem: https://en.wikipedia.org/wiki/Dining_philosophers_problem
  * Solutions
    * Arbitrator solution
      * Allow to pick two forks or none
    * Resource hierarchy solution
      * Last or even people pick left first, others pick right first
    * Limiting #diners
      * Allow at most n-1
    * Chandy/Misra solution
      * This prevents starvation

## MT Data Structures and Algorithms
* `thread-guard.cc` - Implement a thread guard
  * Don't skip join when an exception occurs
    * Need two `join()` in and after the `catch` block
    * Or use a thread_guard RAII class
* `spinlock.cc` - Implement a spinlock using an atomic Boolean
  * `std::atomic_flag flag;`
    * Lock: `while (flag.test_and_set(std::memory_order_acquire));`
    * Unlock: `flag.clear(std::memory_order_release);`
* `mt-accumulate.cc` - Implement a MT accumulate algorithm
  * Thread ID
    * `std::this_thread::get_id()`
  * Arguments to threads
    * Pass by copy by default
    * Use `std::ref()` to force to pass as reference
    * `std::mem_fn` as a wrapper of a member function
  * Measure runtime
    * `#include <chrono>`
    * `std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();`
    * `std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n"`
* `threadsafe-stack.cc` - Implement a thread-safe stack
  * Eliminate race condition, e.g. stack pop() vs. top()
    * Pass in a reference
    * Require a no-throw copy constructor or move constructor
    * Return a pointer to the popped item
    * Provide both option 1 and either option 2 or 3
* `threadsafe-queue.cc` - Implement a thread-safe queue
  * Blocking vs. non-blocking

## Readings
* C++ Concurrency in Action, Second Edition
* Multi-threading library: http://www.cplusplus.com/reference/multithreading/
* Thread support library: https://en.cppreference.com/w/cpp/thread

