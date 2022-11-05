# GNU Tools

To begin, C++ is a an platform agnostic, compiled language meaning that it can be executed on a variety of hardware platforms and operating systems.  Since I tend to support both Windows and Linux platforms, I often find myself using multiple tool chains during development and debugging.  Below is information about a number of GNU tools often associated with the Linux operating system.  Fundamentally though, GNU is an extensive collection of free software, which can be used as an operating system or can be used in parts with other operating systems.

The first two sections discuss the GNU compiler and make system.  An example of their use is documented in the [Compile.md](./Compile.md) markdown file where I hope to walk through in detail their general use.

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
* [lexical analysis](https://en.wikipedia.org/wiki/Lexical_analysis) - parsing source characters into lexical tokens.  This is the initial part of reading and analyzing the program text: The text is read and divided into tokens, each of which corresponds to a symbol in the programming language, e.g., a variable name, keyword or number.
* [syntactic analysis](https://en.wikipedia.org/wiki/Parsing) - analysis of logical rules of the language. This phase takes the list of tokens produced by the lexical analysis and arranges these in a tree-structure (called the syntax tree) that reflects the structure of the program. This phase is often called parsing.
* [semantic analysis](https://en.wikipedia.org/wiki/Semantic_analysis_(compilers)) - context sensitive analysis of language items such are variables for type checking logic.  This phase analyses the syntax tree to determine if the program violates certain consistency requirements, e.g., if a variable is used but not declared or if it is used in a context that does not make sense given the type of the variable, such as trying to use a Boolean value as a function pointer.

Once the abstract syntax tree is created compilation occurs and final assembly and linking.  Machine code generation is where the AST, or some form of intermediate language, is translated to assembly language (a textual representation of machine code) for a specific machine architecture.  For C/C++ this output is stored as binary object files.  The object code is then assembled and linked based on rule sets for the creation of static libraries (.lib, .a), dynamic libraries(.dll, .so), or executables.  

The first set of operations are collectively referred to as the the frontend of the compiler and the last set of operations are collectively referred to as the backend. Often each operation, through checking and transformation, establishes stronger invariants on the things it passes on to the next, so that writing each subsequent phase is easier than if these have to take all the preceding into account. For example, the type checker can assume absence of syntax errors and the code generation can assume absence of type errors.

The gcc and g++ execution have small deviations but follow the same fundamental steps.  The below image is a good reference for remembering the stages.

![GCC compilation pipeline](https://upload.wikimedia.org/wikipedia/commons/9/9a/Preprocessor.png "GCC Compilation Pipeline")
## gmake

Make is a build automation tool for compiling source code into libraries and executables that has a long history.  Originally created by Stuart Feldman in April 1976 at Bell Labs, this tool has gone through multiple iterations, forks, and rewrites.  The most common implementation has to be gmake (GNU Make) which is the standard implementation of Make for Linux. It provides several extensions over the original Make, such as conditionals, built-in functions, and variables.

Fundamentally, gmake is a script interpreter that pass commands to the systems shell for processing based on a set of rules contained within a makefile.  A **rule** in a makefile tells the program how to execute a series of **commands** in order to build a **target** from **source** files.

* rule - combination of commands and variables to accomplish an action
* command - executable and parameters to be passed to the shell
* source - target input file(s)
* target - the goal to be accomplished based on rules

Makefiles are written in a declarative manner where the structure and elements are defined based on the logic of the operations, **the what**, and not the specific execution order, **the how**.

On execution, gmake will by default look in the current directory for a Makefile, decide whether a target needs to be regenerated by comparing file modification times of the source and target.

While most often associated with the compilation of C/C++ files into objects, libraries, and executables, it can be used for almost any language compile and really any scripted process.  involves executing arbitrary commands to transform a source file to a target result.

For more information, check out the projects makefile and writeup [Makefile Writeup](./project/Makefile.md)

For all of the information you could ever want, please refer to the [GMake Official Documentation](https://www.gnu.org/software/make/manual/make.html)

## gprof

gprof calculates the amount of time spent in each routine and is a good first step profiler.  Straight from the man pages for the tool we get:

>"gprof" produces an execution profile of C, Pascal, or Fortran77 programs.  The effect of called routines is incorporated in the profile of each caller.  The profile data is taken from the call graph profile file  (gmon.out default) which is created by programs that are compiled with the -pg option of "cc", "pc", and "f77".  

>The -pg option also links in versions of the library routines that are compiled for profiling. "Gprof" reads the given object file (the default is "a.out") and establishes the relation between its symbol table and the call graph profile from gmon.out.  If more than one profile file is specified, the "gprof" output shows the sum of the profile information in the given profile files.

Great, so how de actually use it.  First step, we need to make sure our application gets built with the -pg option.  We do this by creating the gprof target in our existing makefile to update the flags, perform the build and then execute a run.

```bash
# add -pg flags (p=program instrumentation, g=debug option) to the cpp compile
gprof: CXXFLAGS += -pg
# perform a debug build before running recipe
gprof: debug
# run the application to produce grprof data
	./bin/project
# move the gmon.out file
	mv gmon.out ./bin/gmon.out
# run gprof against the gmon.out and pipe results to the text file
# The -q option causes "gprof" to print the call graph analysis
	gprof -q ./bin/project ./bin/gmon.out > ./bin/gprofdata.txt
```

Now all we need to do is call ```make clean; make debug``` and read the gprofdata.txt in our favorite text editor to review the results.

The entries are sorted by time spent in the function and its subroutines

Field | Meaning
:----: | :----------------
Index | Entries are numbered with consecutive integers.  This same number is referenced in the name
%time | This is the percentage of the `total' time that was spent in this function and its children.  Note that due to different viewpoints, functions excluded by options, etc, these numbers will NOT add up to 100%
Self | This is the total amount of time spent in this function
Children | This is the total amount of time propagated into this function by its children
Called | This is the number of times the function was called. If the function called itself recursively, the number only includes non-recursive calls, and is followed by a `+' and the number of recursive calls
Name | The name of the current function.  The index number is printed after it.  If the function is a member of a cycle, the cycle number is printed between the function's name and the index number

Many times the top few methods are victims of the subroutines so follow the children.  If you happen upon a method that accounts for a large percentage of processing time, generally > ~40% or more of the time, investigate the code and see if there is a way to simplify. If you don’t have the skills to determine a good refactor of the code, phone a friend.  Sometime a second set of eyes can help find the efficiency.  Of course, some functions just take time.  Be careful that you don’t fall into the trap of only concerning yourself on reducing the time it takes to get through a function, many times you can reduce the number of times the function is called and make a bigger impact to performance gains that way.

When you have traced a performance issue down to a method or even a single line of code, you can put timing calipers around the suspect code and pinpoint the exact issue.  This is done by adding instrumentation timing code to the executable itself or leveraging a caliper library.  

In some instances, you can try using compiler options to see if you can aggressively optimize the build in that specific area.

In either case, you will need building a release version and not using grpof for the final performance numbers.
When addressing performance issues, don’t fall into the trap of only concerning yourself on reducing the time it takes to get through the method, many times you can reduce the number of times the function is called and make a bigger impact.


## strace

strace intercepts and records the system calls which are called by the process and the signals which are received by a process

## sprof
sprof calculates the amount of time spent in each routine of a shared object.

## valgrind

valgrind is a flexible program for debugging and profiling Linux executables

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


