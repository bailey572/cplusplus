# The mystery of the Makefile

Ok, let's face it, makefiles are weird.  They have some rules that I am sure made sense at the time but with decades of history they come with bit of baggage.  So much so, I am dedicating a special section just to dig a little deeper into them.

Makefiles are written in a declarative manner where the structure and elements are defined based on the logic of the operations, **the what**, and not the specific execution order, **the how**.  Ok, great.  We deal with declarative scripts in all sorts of tools, so what makes the makefile so interesting.  I am glad that you asked.

## Foundational Concept

A makefile is a collection of *rules* that consists of a *target*, followed by *prerequisites*, and then the *recipe*.  The syntax for a typical rule will follow the format:

```bash
target: prerequisites
	recipe
```

One way that I like to visual a makefile rule as a function declaration with an implicit return value.  Take for example:

```C++
void myFunctionLabel (parameters) // declaration
{
    // body (definition)
}
```

The target is the label for the task, the prerequisites are the parameters, and the recipe is the functions body.  While this is close enough to help align the pieces in your mind, the comparison is not completely accurate, so let's dig a little deeper into what each piece really is.

Much like the label of a function in C/C++, the target is a named handle for that target.  Additionally, or more specifically, the target is actually a file name, how that file name is treated is dependent on the recipe.  For now, just remember that a target can be either a task label or a file name and we will discuss the why in just a bit.

Prerequisites are zero or more dependencies of the target.  Unlike function variables, the dependencies of a target are not passed https://bytes.usc.edu/cs104/wiki/makefile/ (STOPPED HERE)  Dependencies can either be other targets or file names; if a target depends on another target, it guarantees that target will be run prior, and if a target depends on a file, it will check to see if that file has changed to avoid executing redundantly.

```bash
all: program

program: main.cpp file1.o file2.o
	g++ -g -Wall main.cpp file1.o file2.o -o program

file1.o: file1.cpp file1.h
	g++ -g -Wall -c file1.cpp -o file1.o

file2.o: file2.cpp
	g++ -g -Wall -c file2.cpp -o file2.o

clean:
	rm -f *.o program
```
