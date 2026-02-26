*This project has been created as part of the 42 curriculum by nkuydin.*

# Project Name
Philosophers

## Description
Five philosophers who are sitting around a circular table, with a plate of spaghetti in front of each of them, and a single fork between each pair of adjacent philosophers. The goal of each philosopher is to eat the spaghetti, but in order to do so, they must each use two forks.

### Overview
One of the very interesting **features** of the threads is that they don’t have the strict parent-child hierarchy that processes do. The only distinction the ‘main’ thread has is being the first one to exist at the beginning of the process. Meaning,  within the same process, any thread can wait for any other thread to complete, or kill any other thread.



### Goals
The problem is to design a protocol that allows each philosopher to pick up the two forks to their sides without causing a deadlock, where every philosopher is waiting for a fork that is currently being held by their neighbor. The protocol must ensure that no philosopher goes hungry, and that no two adjacent philosophers hold the same fork at the same time.

---

The project demonstrates strong understanding of:

 - Threading concepts
 - Mutex synchronization
 - Race condition prevention
 - Deadlock avoidance
 - Time-critical programming
 
---

## Instructions

### Requirements

- Operating System: Linux or macOS  
- Compiler: `gcc`
- Using of POSIX thread flag:
    -pthread/-lpthread

### Compilation

make \
make all

### Execution

./philo 5 410 200 200 5

## Resources

 - [Multithreading in C](https://www.geeksforgeeks.org/c/multithreading-in-c/)
 - [Basics of Multithreading in C](https://dev.to/quantumsheep/basics-of-multithreading-in-c-4pam#:~:text=🧵%20What%20Is%20a%20Thread,For%20example:)
 - [Threads and Its Types in OS](https://www.geeksforgeeks.org/operating-systems/threads-and-its-types-in-operating-system/)
 - [Difference Between Process and Thread](https://www.geeksforgeeks.org/operating-systems/difference-between-process-and-thread/)
 - [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/#concurrent-programming)
 - [Create threads in a for loop (pthread_create)](https://www.youtube.com/watch?v=xoXzp4B8aQk&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=5)
 - [Valgrind User Manual, Helgrind: a thread error detector](https://valgrind.org/docs/manual/hg-manual.html)
 ##### The MOST Useful Medium Post Ever --->
 - [Explanation of threads on example of Starbucks efficiency](https://medium.com/@jalal92/lets-discuss-threads-grab-a-coffee-ad4d4ebf7181)
 ## AI Usage
 
 + Understanding Fork Assigment
 + Understanding the Precision of Custom Usleep Implementation