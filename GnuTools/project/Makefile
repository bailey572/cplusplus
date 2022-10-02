#-----------------------------------------------------------------------------#
#  EXECUTABLE, SOURCES, OBJECTS AND PROJECT STRUCTURE                         #
#-----------------------------------------------------------------------------#

# Target is the final name for the Executable
TARGET := project

# Project structure defined as local variables
PROJECT_DIRECTORY  := .
APP_DIRECTORY      := bin
OBJECTS_DIRECTORY  := objs
DOCUMENT_DIRECTORY := doc
INCLUDE_DIRECTORY  := inc
LIBRARY_DIRECTORY  := libs
DATA_DIRECTORY     := data
SOURCES_DIRECTORY  := src
TESTS_DIRECTORY    := tests

# C ++ application source code which must be preprocessed using the builtin wildcard function.
# Wildcard expansion happens automatically in rules. But wildcard expansion does not normally
# take place when a variable is set, or inside the arguments of a function. 
SOURCES  := $(wildcard $(SOURCES_DIRECTORY)/*.cpp)

# By default, the object file name for a source file is made by replacing the
# suffix .c, .cpp, .i, .s, etc., with .o.
# $(subst from,to,text) Performs a textual replacement on the text each occurrence of from is replaced by to. 
OBJECTS  := $(patsubst $(SOURCES_DIRECTORY)/%.cpp,$(OBJECTS_DIRECTORY)/%.o,$(SOURCES))

#-----------------------------------------------------------------------------#
#  ENVIRONMENT                                                                #
#-----------------------------------------------------------------------------#

# To avoid trouble on systems where the SHELL variable might be inherited from
# the environment.
SHELL = /bin/sh

# Program for compiling C++ programs; default ‘g++’.
# Apple Mac M1 clange
#CXX := /usr/bin/clang
# Apple Mac GNU
#CXX := /opt/homebrew/bin/g++-12
# Ubuntu/Mint Linux
CXX := g++


# Define library specific directories not expected to be in the environment paths
# Apple Mac M1 brew boost
#BOOST_ROOT := "/opt/homebrew/Cellar/boost/1.79.0_1"
# Ubuntu/Mint Linux boost
BOOST_ROOT := "/usr/include/boost"

# Extra flags to give to the C++ compiler.
# -std: standard or c++17 for the C++ 17 standards
# -pedantic-errors: Issue all the errors demanded by strict ISO C and ISO C++.
# -Wall: Enables all the warnings about constructions.
# -Wextra: Enables some extra warning flags that are not enabled by -Wall.
# -Wshadow: Warn whenever a local variable shadows another local variable,
#           parameter or global variable or a built-in function is shadowed.
# -m64: Generate code for a 64-bit environment.
CXXFLAGS := -std=c++17 -pedantic-errors -Wall -Wextra -Werror -Wshadow -m64

# Extra flags to give to compilers when they are supposed to invoke the linker,
# ‘ld’, such as -L for library directories. 
#Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS := #-L/usr/lib

# Library flags or names given to compilers when they are supposed to invoke
# the linker, 
# ‘ld’. Non-library linker flags, such as -L, should go in the LDFLAGS variable.
LDLIBS := -L$(BOOST_ROOT)/lib #-lstdc++ -lm

# -I dir: Add the directory dir to the list of directories to be searched for header files.
# C, C++ , Objective-C or Objective-C++ header file to be turned into a precompiled header.
INCLUDES := -I$(BOOST_ROOT)/include \
           -I$(INCLUDE_DIRECTORY)

# Command to remove a file; default ‘rm -f’.
# r: recursive, v: verbose, f: force.
RM = rm -rvf

# Make directory if it does not exist.
# p: Create intermediate directories as required, v: Create intermediate directories as required
MKDIR_P := mkdir -p -v

#-----------------------------------------------------------------------------#
#  RECIPES                                                                    #
#-----------------------------------------------------------------------------#

# A phony target is one that is not really the name of a file; rather it is just a name for a recipe to be
# executed when you make an explicit request.
.PHONY: all build clean debug release test grprof

# Make all the top-level targets the makefile knows about. First calls target build and then $(APP_DIRECTORY)/$(TARGET)
all: build $(APP_DIRECTORY)/$(TARGET)

# The rule that links libraries to the target.
# -o outfile: Place output in file outfile. If -o is not specified, the default
#             is to put an executable file in a.out.
# $@: The file name of the target.
# $^: The names of all the prerequisites, with spaces between them.
$(APP_DIRECTORY)/$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o $@ $^ $(LDLIBS)
#	@echo "Copying target to project directory..."
#	cp $(APP_DIRECTORY)/$(TARGET) $(PROJECT_DIRECTORY)/$(TARGET)

# The rule that compiles ‘.cpp’ files into ‘.o’ files.
# The recipe uses the automatic variables ‘$@’ and ‘$<’ to substitute the names
# of the target file and the source file in each case where the rule applies.
# $@: The file name of the target.
# $<: The name of the first prerequisite.
$(OBJECTS): $(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.cpp
	@echo "Compiling objects..."
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

# When a line starts with ‘@’, the echoing of that line is suppressed. The ‘@’
# is discarded before the line is passed to the shell. Typically you would use
# this for a command whose only effect is to print something, such as an echo
# command to indicate progress through the makefile.
build:
	@echo "Building directories..."
	@$(MKDIR_P) $(APP_DIRECTORY)
	@$(MKDIR_P) $(OBJECTS_DIRECTORY)
	@$(MKDIR_P) $(DOCUMENT_DIRECTORY)
	@$(MKDIR_P) $(DATA_DIRECTORY)
	@$(MKDIR_P) $(INCLUDE_DIRECTORY)
	@$(MKDIR_P) $(LIBRARY_DIRECTORY)
	@$(MKDIR_P) $(SOURCES_DIRECTORY)
	@$(MKDIR_P) $(TESTS_DIRECTORY)
	@$(MKDIR_P) $(TESTS_DIRECTORY)/$(APP_DIRECTORY)

# -g: Produce debugging information in the operating system's native format.
debug: CXXFLAGS += -DDEBUG -g
debug: all

# -O0: Reduce compilation time and make debugging produce the expected results.
#      This is the default.
# -O1: Optimize. Optimizing compilation takes somewhat more time, and a lot
#      more memory for a large function.
# -O2: Optimization flag. GCC performs nearly all supported optimizations that
#      do not involve a space-speed tradeoff.
# -O3: Optimize even more. -O3 turns on all optimizations specified by -O2 and
#      also turns on other optimization flags.
# -Os: Optimize for size. -Os enables all -O2 optimizations that do not
#      typically increase code size. It also performs further optimizations
#      designed to reduce code size.
release: CXXFLAGS += -O2
release: all

# Delete all files (and directories) that are normally created by running make.
clean:
	@echo "Cleaning..."
	@$(RM) $(OBJECTS_DIRECTORY)
	@$(RM) $(APP_DIRECTORY)/$(TARGET)
	@$(RM) $(TARGET)
	@$(RM) $(TESTS_DIRECTORY)/$(APP_DIRECTORY)

# Wildcard is a built in function for filenames. If TESTS_DIRECTORY has files named 'foo.cpp bar.cpp max.txt', 
# TEST_SRCS will only contain 'foo.cpp bar.cpp'.
TEST_SRCS := $(wildcard $(TESTS_DIRECTORY)/*.cpp)
# ':%.cpp=%' is a substitution reference. In this case, if TEST_SRCS has values 'foo.cpp bar.cpp', 
# TEST_BINS will have values 'foo bar'.
TEST_BINS := $(TEST_SRCS:%.cpp=%)

# For unit tests, we first built the project (release) before creating and runnig the tests
test: release $(TEST_BINS)

# Use a pattern rule, a pattern rule looks like an ordinary rule, except that its target contains the character ‘%’ (exactly one of them). 
# The target is considered a pattern for matching file names; the ‘%’ can match any nonempty substring, while other characters match only 
# themselves. The prerequisites likewise use ‘%’ to show how their names relate to the target name.
# So For each entry in TEST_BINS we execute the compile command
%: %.cpp
	$(CXX) $(INCLUDES) -o $(TESTS_DIRECTORY)/$(APP_DIRECTORY)/$(@F).test $^
# Once test module is built, run the test and log the results
# Boost Unit test supports three output options HRF=Human Readable Format, CLF=command line feed ,XML=XML
# and the following log levels all|success|test_suite|unit_scope|message|warning|error|cpp_exception|system_error|fatal_error|nothing
	$(TESTS_DIRECTORY)/$(APP_DIRECTORY)/$(@F).test --output_format=CLF --log_level=all > $(TESTS_DIRECTORY)/$(APP_DIRECTORY)/$(^F)-report.log

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