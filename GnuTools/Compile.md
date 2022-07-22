# Compilation using GNU tools (gcc and gmake)

## Directory Structure

C++ allows for infinite customization and the build systems supporting it follow the same philosophy.  What does that mean exactly?  Well, it means that if you can dream of a project layout, you can make it happen and there is not definitive setup required for a C/C++ project.  With that freedom however comes the ability to create an infinite number of pits to fall into.

That being said, if you look around at enough projects you will begin to see a pattern emerge.  Sprinkle in my own preferences and I tend to gravitate towards a project pattern that generally looks like this.

```bash
Project_name
  |
  |---- makefile
  |
  |---- bin
  |
  |---- data
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

* Makefile - this single file located in the root of the project diretory will be responsible for orchestrating the entire build operation
* bin - is the directory where we will store the compiled executable files that we build
* data - directory to store any support data, files, documentation, or scripts that the project may need
* inc - collection of an include files that will be publicly distributed with compiled library files for other projects consumption.
* libraries - collection of third party libraries that will be leveraged by the project
* libs - is the directory where we will store the compiled libraries (static and dynamic) files that we build
* objs - staging directory for objects built during compilation to keep source area clean
* src - primary source code for the project where each module directory contains an inc and src directory
  * inc - collection of private header files for the module
  * src - modules raw source code
* test - source code for the projects unit tests
## Install GNU tools
```bash
brew install gcc
brew install make
```
GNU "make" has been installed as "gmake".
If you need to use it as "make", you can add a "gnubin" directory
to your PATH from your bashrc like:

     PATH="$(brew --prefix)/opt/make/libexec/gnubin:$PATH"

## Install Boost

I am doing this on a Mac, Apple sucks so I suggest using [Homebrew](https://brew.sh/)

```bash
brew install boost
```

1.76.0	Collection of portable C++ source libraries