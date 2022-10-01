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
Please note, my descriptions may not be as accurate as the [make document](https://www.gnu.org/software/make/manual/make.html#How-Make-Works), but are accurate to the level we need them at this point.

The **target** is the label for the task, the **prerequisites** are targets or commands that need to occur before executing the target, and the **recipe** is the actual rules that will be executed.

### Target

Much like the label of a function in C/C++, the target is a named handle for that target.  Additionally, or more specifically, the target is actually a file name, how that file name is treated is dependent on the recipe.  For now, just remember that a target can be either a task label or a file name and we will discuss the why in just a bit.

### Prerequisites

Prerequisites are zero or more dependencies the target requires to be executed prior to its own processing.  These can be variable assignment, inline functions, or calls to additional targets.  If a target depends on another target, it guarantees that target will be run prior, and if a target depends on a file, it will check to see if that file has changed to avoid executing redundantly.  When reading a list of prerequisites, you should read them from right to left as that is how they will be executed.

For example:

```bash
$(OBJECTS): $(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.cpp
```

The target ```$(OBJECTS)``` and its prerequisites ``$(OBJECTS_DIRECTORY)/%.o and $(SOURCES_DIRECTORY)/%.cpp.  $(SOURCES_DIRECTORY)/%.cpp`` will be executed first, followed by ```$(OBJECTS_DIRECTORY)/%.o```, and only then will the target ```$(OBJECTS)``` recipe be executed.

### Recipe

Last but not least we have the recipe.  The recipe is one or more sequential steps that can consist of shell script, shell commands, additional targets, built in functions or just about anything else one could want.

The kicker is that **each item in a recipe must be proceeded by the tab character**.  A **REAL** tab character, ala ASCII code 09 = HT (Horizontal Tab) and not just white space.  Space, ASCII code 20, will look right but fail to execute the line.

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

Ok, now that we have an understanding of the basic processing of a makefile, lets dig into variable support.

First and foremost, variables in makefiles are text strings.  While you can put numbers and all sorts of other crazy things into a makefile variable, they are stored and treated like strings.  The value for variables are expanded when read, meaning that you can use plain text or append other variable or even results from executed commands.

### Declaration

Declaration and setting of a variable is pretty straight forward and generally come in one of three flavors.

```bash
variable = "my value"
variable := "my value"
variable ::= "my value"
```

please note, the quotes in the above example are actually not required but is a good idea for controlling exactly what is ingested.

Variables defined with ‘=’ are recursively expanded variables. Variables defined with ‘:=’ or ‘::=’ are simply expanded variables; these definitions can contain variable references which will be expanded before the definition is made.

Another often used assignment operator that you will run across is conditional assignment ?= operator.

This is used whn you would like the variable to set to a value, only it is has not already been set.

```bash
FOO ?= bar
```

Which is short hand for something like this

```bash
ifeq ($(x), undefined)
y = $(x)
endif
```

### Dereference

To dereference a variable to access its contents, the dollar sign '$' is used.

```bash
x = "hello"
y = $(x)
```

Please note, the parentheses are required when referencing a variable but you may also run across brackets {} as well.  Parentheses () and brackets {} are treated the same by make.

### Append

To append values to a variable, the += operator is used.

```bash
x = "hello"
x += " world"
```

Variable references in the right-hand side will be expanded if and only if the original variable was defined as a simply-expanded variable.  More on those below.

### Recursively Expanded Variables

When defining a recursively-expanded variable, the contents of the right-hand side are stored as-is. If a variable reference is present, the reference itself is stored **not the value of the variable**. Make waits to expand the variable references until the variable is actually used.

```bash
x = hello
y = $(x) # Both $(x) and $(y) will now yield "hello"
x = world # Both $(x) and $(y) will now yield "world"
```

In the above example, the definition of y is recursive. The reference to $(x) doesn't get expanded until $(y) is expanded. This means that whenever the value of x changes, the value of y will change as well.

Recursively-expanded variables are a powerful but are easy to misunderstoodl. They can be used to create constructs that resemble templates or functions, or even to automatically generate portions of a makefile. They can also be the source of hard-to-debug problems. Be careful to only use recursively-expanded variables when necessary.

### Simply Expanded Variables

Simply-expanded variables behave like variables from traditional programming languages. The expression on the right-hand side is evaluated, and the result is stored in the variable. If the right-hand side contains a variable reference, that variable is expanded before the assignment takes place.

Single- and double-colon assignment are equivalent. The POSIX make standard only mentions the ::= form, so implementations with strict standards compliance may not support the single-colon declaration but I have not run across one.

```bash
x := hello
y ::= $(x) # Both $(x) and $(y) will now yield "hello"
x := world # $(x) will now yield "world", and $(y) will yield "hello"
```

### Automatic Variables

Make also supports a number of special variables.  These variables can have a different value for each rule in a makefile and are meant to make writing rules simpler. The automatic variables can only be used in the recipe portion of a rule i.e. assigned while processing.

Variable | Description
:------: | ---------------------
$@ | File name of the rule's target
$% | The target member's name, if the rule's target is an archive
$< | File name of the first prerequisite
$^ | List of all prerequisites
$? | List of all prerequisites that are newer than the target
$* | The "stem" of an implicit or pattern rule

## A simple example

If you have pulled down this repository, you will find a heavily commented [makefile](./Makefile) in the same directory as this markdown file.  The comments should give anyone a pretty good idea as to what is going on but a little bit of help is always nice

The top section contains a collection of simply expanded variables defining the environment, some shell commands, and the binaries name.

The rest of the file contains the definitions for all of the targets (all, build, clean, debug, release, & test), their prerequisites, and recipes.

Target | Description
:----: | :-----------------------
all | Default target and calls the build target before building the source code and linking the final application
build | Builds the needed temporary directories, not the code
clean | Removes the temporary directories
debug | sets compiler flags variable before calling all
release | sets compiler flags variable before calling all
test | calls release before building and running the boost unit test based files before executing each test

Before you try and run the file, make sure you look at the system you will be running on and used the correct values for CXX and BOOST_ROOT.

## Summary

There is a lot more to variables in makefiles but this will get you started.  

Check out the [make document](https://www.gnu.org/software/make/manual/make.html#How-Make-Works) for further information and to delve into some cool subjects like nested variables or computed variable names.

Also, there is a pretty good quick reference at [Rip Tutorial](https://riptutorial.com/makefile).

 