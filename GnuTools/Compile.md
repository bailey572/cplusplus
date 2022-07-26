# Compilation using GNU tools (gcc and gmake)

## Directory Structure

C++ allows for infinite customization and the build systems supporting it follow the same philosophy.  What does that mean exactly?  Well, it means that if you can dream of a project layout, you can make it happen and there is not definitive setup required for a C/C++ project.  With that freedom however comes the ability to create an infinite number of pits to fall into.

That being said, if you look around at enough projects you will begin to see a pattern emerge.  Sprinkle in my own preferences and I tend to gravitate towards a project pattern that generally looks like this.

```bash
Project_name
  |
  |---- Makefile
  |
  |---- bin
  |
  |---- data
  |
  |---- doc
  |
  |---- inc
  |       |
  |       |---- Module_name
  |                 |
  |                 |---- public_header(s).h
  | 
  |---- libraries
  |       |
  |       |---- Third Party A
  |       |
  |       |---- Third Party B
  |
  |---- libs
  |       |
  |       |---- Module_name
  |
  |---- objs
  |       |
  |       |---- Module_name
  |              |----code.o
  |
  |---- src
  |       |
  |       |---- Module_name
  |              |
  |              |----inc
  |                    |---- private_header(s).h
  |
  |              |----src
  |                    |---- code(s).cpp
  |
  |---- tests
  |       |
  |       |---- Module_name
  |               |
  |               |---- unit_test(s).cpp
```

Great! so what does that all mean? Well lets break it down.

* Makefile - this single file located in the root of the project directory will be responsible for orchestrating the entire build operation to include calling additional Magefiles if required.  The root directory is recommended but can be overridden through the command line
* bin - is the directory where we will store the compiled executable files that we build (only applicable to applications)
* data - directory to store any support data, files, or scripts that the project may need to build or run
* doc - documentation for the project.  Often located in the data but a separate directory is cleaned in my opinion
* inc - collection of included header files that will be publicly distributed with compiled library files for external projects consumption.
* libraries - collection of third party libraries and header files that will be leveraged by the project
* libs - directory where we will store compiled libraries (static and dynamic) files that we build
* objs - staging directory for objects built during compilation to keep source area clean
* src - source code for the project where each module directory contains an inc and src directory
  * inc - collection of private header files for the module
  * src - modules raw source code
* test - source code for the projects unit tests

## Install GNU tools

I am writing this while working on a Mac and a Linux Mint box.  By default, Mac uses clang so to install the Gnu tools, I leveraged the [Homebrew](https://brew.sh/) package manager.  To install brew, follow the installation instructions on their [Homepage](https://brew.sh/).  
Once complete, you should be able to install the the gnu tools with the following commands.

```bash
brew install gcc
brew install make
```


## Install Boost

I am doing this on a Mac, Apple sucks so I suggest using 

```bash
brew install boost
```

1.76.0	Collection of portable C++ source libraries