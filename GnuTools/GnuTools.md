# GNU Tools
To begin, C++ is a an Agnostic language, compiled language meaning that it can be executed on a variety of hardware platforms and operating systems.  Since I tend to support both Windows and Linux platforms, I often find myself using multiple tool chains during development and debugging.  Below is information about a number of GNU tools often associated with the Linux operating system.  Fundamentally though, GNU is an extensive collection of free software, which can be used as an operating system or can be used in parts with other operating systems. 

## gcc/g++

## make

## gprof
gprof calculates the amount of time spent in each routine.

## strace
strace intercepts and records the system calls which are called by the process and the signals which are received by a process

## sprof
sprof calculates the amount of time spent in each routine of a shared object.

## valgrind
valgrind is  a flexible program for debugging and profiling Linux executables

```Usage: valgrind --tool=toolname program args```

Tools:
* memcheck: is a fine-grained memory checker
* cachegrind: is a cache simulator. Annotates every line of program with the number of instructions executed and cache misses incurred
* Callgrind: adds call graph tracing to cachegrind.
* Massif: a heap profiler. Measures heap memory usage.

### memcheck 
```usage: --tool=memcheck```
memcheck is valgrind’s heavyweight checking tool. All reads and writes of memory are checked, and calls to malloc/new/free/delete are intercepted.

Detects:
* Use of uninitialized memory
* Reading/writing memory after it has been free’d
* Reading/writing off the end of malloc’d blocks
* Reading/writing inappropriate areas on the stack
* Memory leaks – where pointers to malloc’d blocks are lost forever
* Mismatched use of malloc/new/new[] vs free/delete/delete[]
* Overlapping src and dst pointers in memcpy() and related functions

### cachegrind
cachegrind is a tool for finding places where programs interact badly with typical modern superscalar processors and run slowly as a result. In particular, it will do a cache simulation of your program, and optionally a branch predictor simulation, and can then annotate your source line-by-line with the number of cache misses and branch mis-predictions.

cachegrind collected statistics
* L1 instruction cache reads and misses
* L1 data cache reads and read misses, writes and write misses
* L2 unified cache reads and read misses, writes and write misses.
* Conditional branches and mis-predicted conditional branches
* Indirect branches and mis-predicted indirect branches. An indirect branch is a jump or call to a destination only known at run time.

### massif
```usage: --tool=massif```
Massif is a heap profiler. It measures how much heap memory your program uses. This includes both the useful space, and the extra bytes allocated for book-keeping purposes and alignment purposes. It can also measure the size of your program’s stack, although it does not do so by default.

Reducing memory footprint can speed up your program as they will avoid paging and cache misses. It will also reduce dependency on the slow swap space.

Massif can also indicate memory leaks that memcheck will miss. If a pointer is still reachable at termination, memcheck will miss this as a memory leak.

Output from this tool produces a memory graph snapshot
* Normal snapshots are indicated by ‘:’ and ‘.’
* Detailed snapshots are indicated by ‘@’ or ‘,’


