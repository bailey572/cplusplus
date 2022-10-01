# The mystery of the Makefile

Ok, let's face it, makefiles are weird.  They have some rules that I am sure made sense at the time but with decades of history they come with bit of baggage.  So much so, I am dedicating a special section just to dig a little deeper into them.

Makefiles are written in a declarative manner where the structure and elements are defined based on the logic of the operations, **the what**, and not the specific execution order, **the how**.  Ok, great.  We deal with declarative scripts in all sorts of tools, so what makes the makefile so interesting.  I am glad that you asked.

## Foundational Concept

A makefile is a collection of *rules* that consists of a *target*, followed by *prerequisites*, and then the *recipe*.  The syntax for a typical rule will follow the format:

```bash
target: prerequisites
	recipe
```

Wow, that is a lot of words that, if you are like most people, do not tell you crap, so let's break that down a bit.
Please note, my descriptions may not be as accurate as the make document, but are accurate to the level we need them at this point.

The **target** is the label for the task, the **prerequisites** are targets or commands that need to occur before executing the target, and the **recipe** is the actual rules that will be executed.

### Target

Much like the label of a function in C/C++, the target is a named handle for that target.  Additionally, or more specifically, the target is actually a file name, how that file name is treated is dependent on the recipe.  For now, just remember that a target can be either a task label or a file name and we will discuss the why in just a bit.

### Prerequisites

Prerequisites are zero or more dependencies the target requires to have executed prior to its own processing.  These can be variable assignment, inline functions, or calls to additional targets.  If a target depends on another target, it guarantees that target will be run prior, and if a target depends on a file, it will check to see if that file has changed to avoid executing redundantly.  When reading a list of prerequisites, you should read them from right to left as that is how they will be executed.

For example:

```bash
$(OBJECTS): $(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.cpp
```

The target $(OBJECTS) and the prerequisites $(OBJECTS_DIRECTORY)/%.o and $(SOURCES_DIRECTORY)/%.cpp.  $(SOURCES_DIRECTORY)/%.cpp will be executed first, followed by $(OBJECTS_DIRECTORY)/%.o, and only then will the target $(OBJECTS) recipe be executed.

### Recipe

Last but not least we have the recipe.  The recipe is one or more sequential steps that can consist of shell script, shell commands, additional targets, built in functions or just about anything else one could want.

The kicker is that **each item in a recipe must be proceeded by the tab character**.  A **REAL** tab character, ala ASCII code 09 = HT ( Horizontal Tab ) and not just white space.  Space, ASCII code 20, will look right but fail to execute the line.

For further clarification, let's review the following makefile source.

```bash
all: program
	@echo "Finished program"

program: main.cpp file1.o file2.o
	@echo "Compiling main.cpp"
	g++ -g -Wall main.cpp file1.o file2.o -o program

file1.o: file1.cpp file1.h
	@echo "Building file1.o"
	g++ -g -Wall -c file1.cpp -o file1.o

file2.o: file2.cpp
	@echo "Building file2.o"
	g++ -g -Wall -c file2.cpp -o file2.o

clean:
	rm -f *.o program
```

As you can see, there are five separate targets in this example (all, program, file1.o, file2.c, and clean).  

If you were to call the clean target, ```make clean```, only a single target would be executed, whose recipe consists of a single shell command rm -f on all *.o files and the "program" directory within the current directory.

Pretty straight forward right?

If you were to call the all target, ```make all```, the first thing to be executed would be the ```all``` targets prerequisite target ```program```, ```programs``` children prerequisite targets ```main.cpp file1.o file2.o``` , the children prerequisites  ```file1.cpp file1.h & file2.cpp```, the children's recipes, the ```program``` recipte, and finally the ```all``` targets recipe.  The echo statements would produce the following:

```bash
Building file1.o
Building file2.o
Compiling main.cpp
Finished program
```

But wait, what about the target main.cpp?  Well, it gets called before file1 or file2, but it does not have a named target. What it does have is a file, and this is processed by the default make rules where the presence of the main.ccp file will execute the targets recipe.

You can prove this by creating a makefile, file2.cpp, file1.cpp, main.cpp.  Populate the files and run make all.

If you want to make it a little easier and just see the steps in action, just create and populate a make file with the following content.

```bash
all: program
	@echo "Finished program"

program: file1.o file2.o
	@echo "Compiling main.cpp"

file1.o:
	@echo "Building file1.o"

file2.o:
	@echo "Building file2.o"
```

This demonstrates the steps and can be a fun way to play with rules.

## Playing with Variables
