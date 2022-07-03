# GNU Tools
To begin, C++ is a an Agnostic language, compiled language meaning that it can be executed on a variety of hardware platforms and operating systems.  Since I tend to support both Windows and Linux platforms, I often find myself using multiple tool chains during development and debugging.  Below is information about a number of GNU tools often associated with the Linux operating system.  Fundamentally though, GNU is an extensive collection of free software, which can be used as an operating system or can be used in parts with other operating systems. 

## GCC/g++
GCC is the GNU Compiler Collection supporting multiple programming languages, hardware architecture, and operating systems.  While there are multiple options, I tend to gravitate to GCC specifically because it is the standard compiler for most GNU project, including the Linux kernel itself, and has been ported to more platforms and instruction set architectures than any other compiler.

While GCC is almost everywhere, other systems have adopted other tool stacks such as Clang for BSD and Apples Mac OS, Microsoft Visual C++ for Windows, and even specific compilers such as Intel's C++ compiler.  In short, there are [a lot](https://en.wikipedia.org/wiki/List_of_compilers) of options to choose from depending on your needs but once you learn one, it is fairly simple to pick up other as required.

Please note, this does not make GCC the best compiler out there, just the most flexible.  This flexibility means that you can almost always fall back to its use but it also tends to bring with it the most overhead and complexity due to its age and being a swiss army knife of compilers, but is often viewed as the standard for both compilation flags and even unofficial language extensions.  In fact, GCC and GMake, GNU Make, have enough gotchas, I will do a separate write up for them in [Compilation using GNU tools](Compile.md).

While GCC supports multiple languages, each language compilation follows the [Unix philosophy](https://en.wikipedia.org/wiki/Unix_philosophy) where each component is a simple tools performing a limited, well defined set of functions that are chained together to complete the compilation task.  In the case of GCC for C++, you will invoke GCC with the executable g++ **(Front End)** with command arguments to call the actual compiler **(Middle End)**, which then runs the assembler, and then the linker if needed in order to produce an executable binary **(Back End)**.

Sound like a lot?  It is.  There are full courses and countless books dedicated to the complexity of compilation of source code into executable units.  While we are not going to cover them in depth here, I do want to capture the fundamentals of the g++ path below.

Fundamentally, GCC follows a three stage architecture **(Front End, Middle End, Back End)** executed in a linear manner as depicted in 
![Three Stage Architecture](https://upload.wikimedia.org/wikipedia/commons/c/cc/Compiler_design.svg "Compiler Design")

With g++, the **Front End** is responsible for initial execution, verification of execution dependencies, interpretation of user options, and orchestration of the run.  Verification of execution dependencies seems like a simple task such as making sure a file exists but goes far further than first glance.  The **Front End** not only has to look for the existence of the source code but also parse its contents.  In the case of C++ this not only consists of the content of .cpp files but also any dependency called out through included statement recursively embedded.  This is accomplished through the [Recursive_descent_parser](https://en.wikipedia.org/wiki/Recursive_descent_parser) responsible for the creation of the [abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) through [preprocessing](https://en.wikipedia.org/wiki/Preprocessor), [lexical analysis](https://en.wikipedia.org/wiki/Lexical_analysis), [syntactic analysis](https://en.wikipedia.org/wiki/Parsing), and [semantic analysis](https://en.wikipedia.org/wiki/Semantic_analysis_(compilers)).  Each of the previous links are worth a read but fundamentally you can think of each as:
* [abstract syntax tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) - structural, content related tree representation of the source code
* [preprocessing](https://en.wikipedia.org/wiki/Preprocessor) - execute instructions to modify code prior to lexical analysis
* [lexical analysis](https://en.wikipedia.org/wiki/Lexical_analysis) - parsing source characters into lexical tokens
* [syntactic analysis](https://en.wikipedia.org/wiki/Parsing) - analysis of logical rules of the language
* [semantic analysis](https://en.wikipedia.org/wiki/Semantic_analysis_(compilers)) - context sensitive analysis of language items such are variables for type checking logic

The gcc and g++ execution have small deviations but follow the same fundamental steps.  The below image is a good reference for remembering the stages.

![GCC compilation pipeline](https://upload.wikimedia.org/wikipedia/commons/9/9a/Preprocessor.png "GCC Compilation Pipeline")
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


