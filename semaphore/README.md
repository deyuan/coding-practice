# Semaphore

## POSIX Semaphore
* Counter + queue
* https://en.wikipedia.org/wiki/Semaphore_(programming)
* Operations
  * P: wait (decrease by 1 or wait, acquire)
  * V: signal (increase by 1, release)
* APIs
  * `sem_wait(sem_t *sem)`
    * P, acquire
  * `sem_post(sem_t *sem)`
    * V, release
  * `sem_getvalue(sem_t *sem, int *value)`
    * Get value of a semaphore by pointer
  * `sem_init(sem_t *sem, int pshared, unsigned int value)`
    * Initialize an unnamed semaphore
    * pshared: 0 for threads within the process, non-zero for IPC
    * value: initial value
  * `sem_destroy(sem_t *sem)`
    * Destroy (paired with sem_init)
  * `sem_open(const char *name, int oflag, int mode, unsigned int value)`
    * Initialize or open a named semaphore
    * name: e.g. `"/mysem"`
    * oflag:
      * O_CREATE: open or create if needed
      * O_EXCL: fail if already exist
    * mode:
      * S_{IR,IW}{USR,GRP,OTH}
      * Open in read/write mode for user/group/others
  * `sem_close(sem_t *sem)`
    * Close (paired with sem_open)
  * `sem_unlink(const char *name)`
    * Delete a named semaphore
* If on OS X
  * Do not use unnamed semaphore, sem_init, sem_destroy or sem_getvalue
  * Do not explicitly link pthread library with `-lpthread`
* Notes
  * Check returned errno value
  * Max value of semaphore is limited by system, and sem_post may error out

## Semaphore in C++20
* Counting semaphore and binary semaphore
  * https://en.cppreference.com/w/cpp/header/semaphore
  * `std::counting_semaphore<1> sem(0);`
  * `std::binary_semaphore sem(0);`
* APIs
  * `acquire`: Decrease the counter or block
  * `release`: Increase the counter
  * `try_acquire/try_acquire_for/try_acquire_until`: Non-block acquire
  * `max`: Return the max possible value

