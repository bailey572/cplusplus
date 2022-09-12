# Compilation using GNU tools (gcc and gmake)

## Directory Structure

C++ allows for infinite customization and the build systems supporting it follow the same philosophy.  What does that mean exactly?  Well, it means that if you can dream of a project layout, you can make it happen and there is no definitive setup required for a C/C++ project.  With that freedom however comes the ability to create an infinite number of pits to fall into.

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
  |
  |---- tests
  |
```

Great! so what does that all mean? Well lets break it down.

* Makefile - this single file located in the root of the project directory will be responsible for orchestrating the entire build operation to include calling additional Magefiles if required.  The root directory is recommended but can be overridden through the command line
* bin - is the directory where we will store the compiled executable files that we build (only applicable to applications)
* data - directory to store any support data, files, or scripts that the project may need to build or run
* doc - documentation for the project.  Often located in the data but a separate directory is cleaned in my opinion
* inc - collection of header files
* libraries - collection of third party libraries and header files that will be leveraged by the project
* libs - directory where we will store compiled libraries (static and dynamic) files that we build
* objs - staging directory for objects built during compilation to keep source area clean
* src - source code for the project
* test - source code for the projects unit tests

Of course, this can be extended in a myriad of ways.  One of my favorites is to put a top level makefile to call into individual modules that I store under the src directory, each with their own makefiles.  These are called by a top level makefile that is basically only for creating global variables that are exported and iterating over the sub directories.

If your environment is all setup, lets go ahead and more over to [Projects Makefile](./project/Makefile.md).  If not, feel free to keep reading to see what I had to do.

## Quick installation for me

I am writing this while working on a Mac M1 arm chip and sometimes a Linux Mint box.  By default, Mac uses clang so to install the additional tools, I leverage the [Homebrew](https://brew.sh/) package manager.  To install brew, follow the installation instructions on their [Homepage](https://brew.sh/).

### Install GNU tools

To install the gnu tools with Homebrew (MAC).
  
```bash
brew install gcc
brew install make
```

To install the gnu tools on mint (Linux).

```bash
sudo apt install gcc
sudo apt install make
```

### Install Boost

While you can compile from source, you can also just install the libraries

To install with Homebrew (MAC).
  
```bash
brew install boost
```

To install on mint (Linux).

```bash
sudo apt install boost
```