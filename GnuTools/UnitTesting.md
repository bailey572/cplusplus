# Unit Testing

In case you need a refresher, unit testing should always be considered first and foremost automated.  I am not certain what decade manual unit testing was considered a good practice but I assure you it was not this century.  If you are looking for a more complete definition, I recommend referring to the [Wikipedia](https://en.wikipedia.org/wiki/Unit_testing) definition.
>unit testing is a software testing method by which individual units of source code—sets of one or more computer program modules together with associated control data, usage procedures, and operating procedures—are tested to determine whether they are fit for use.

Fundamentally, if you build it, you test it.  

Ideally, this would include each function, each class, each functional path.  Realistically, your mileage will vary based on your needs and what you can afford.  At a minimum, I would recommend that you consider public interfaces as the bare minimum as acceptable.

Now that we have that out of the way, your next question should be "how do we do this"?  Why, a framework of course and while you are free to roll your own, I would like to discourage that thought and encourage you to investigate the myriad of options available to you.  Don't believe me? Take a look at the [Wikipedia's List of unit testing frameworks](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks).  That does not even take in to account the many of the smaller open source implementations that you can find on github.

If you are just starting out and working in C/C++, I would suggest looking into the unit test framework that comes with [boost](https://www.boost.org/).  

Why you may ask?  Chances are, if your project gets to any level of complexity, there is a good chance that you will be bringing in boost library anyway.  The boost test library not only provides you with the ability to easily write and execute individual unit test outside of your source code but it also allows you to continue to grow into full test suites.  Of course, with this much capability comes a whole lot of reading and I suggest you take a look at the official [Boost Test Library: Unit Test Framework](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/utf/index.html) but I have written up a quick start guide below with a few interesting notes to get you going.

## Getting started

### Boost Unit Test Library

The boost unit test library is comprised of five individual components, listed below and pulled from the [official documentation](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/index.html).

* **The Execution Monitor** - a basic exception and error detection and reporting facility for use in both production and test programs. The Execution Monitor calls a user-supplied function and reports all caught runtime exceptions. It is used internally by other Boost Test Library components. It also could be used in some production environment to make controlled calls of functions which might otherwise crash the program.
* **The Program Execution Monitor** - a simple helper facility to be used to monitor a program execution. The Program Execution Monitor provides the function main() and uses the Execution Monitor to control a program execution. It should be used in production environment to produce uniform error reports. To control programs working in test environment, use the Unit Test Framework instead.
* **The Test Tools** - a toolbox for various testing needs. Test Tools are used by test programs working under control of the Unit Test Framework.
* **The Unit Test Framework** - a framework that simplifies writing and organizing test cases. The framework supports test cases written as simple free functions or member functions and organizes them into a tree of test suites. The framework allows to use the Test Tools to implement a test cases and provides a facility to manage a log report level and a result report level.
* **The Minimal Testing Facility** - simple facility designed to provide the functionality presented by the original version of Boost.Test. It causes the test program to run in a monitored environment. In addition it defines several simple test tools that behave similarly to ones defined in the Unit Test Framework test tools. Minimal testing facility does not require linking with external components, so could be a component of choice for simple and quick testing needs.

### Unit Test Framework

While all of this is important, for this writeup we are going to mainly focus on the unit test framework, which itself is also comprised of a collection of component.  Again, listed below and pulled from the [official documentation](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/utf/components/index.html).

* **The Test Case** - encapsulates the notion of a testing unit
* **The Test Suite** - allows to unite several related testing units into one bundle that could be considered an a compound testing unit.
* **The Test Log** - responsible for testing logs presentation
* **The Test Result** - responsible for testing results presentation

For the purpose of this quick start, we really only need to focus on associating our test code with the framework and having it run.  Fortunately, boost provides a simple entry point through a main function. Function main() does a lot of good stuff under the hood including

* Initializing the framework
* Setting up parameters based on command line arguments and/or environment variables
* Calling the user-supplied function init_unit_test_suite (more on this in a bit)
* Running the test suite

The framework does all of this while keeping track of all passed/failed assertions, testing progress, and finally generating a result report.  Sounds pretty good right but how do I make it all go?

Fear not, we are getting there.  One last thing I would like to bring to your attention is that boost provides a lot of flexibility in how you can bring all of this in.  The first thing to that you must ask yourself is how cotrolled do you want your setup to be?  The **The Unit Test Framework** supports four different usage variants, again pulled from the [official documentation](https://www.boost.org/doc/libs/1_37_0/libs/test/doc/html/utf/user-guide/usage-variants.html).

* [The static library variant](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/html/utf/user-guide/usage-variants/static-lib-variant.html) - link test modules source file to a single static library (quick compile, larger test files)
* [The dynamic library variant](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/html/utf/user-guide/usage-variants/dynamic-lib-variant.html) - link test modules source file to a single dynamic library (saves disk space)
* [The single-header variant](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/html/utf/user-guide/usage-variants/single-header-variant.html) - Pull in a single header for compilation into the test modules source files themselves (longer compile time and storage need but lower link dependencies)
* [The external test runner variant](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/html/utf/user-guide/usage-variants/extern-test-runner-variant.html) - Build the test runner as a dynamic library for common use by external test running tools (most complex case)

While each has its place they all follow the same general steps.  For this write up, we are going with the most portable option, the single-header variant.

To get started, make sure you have the boost library installed and available in your environments path.  You should find installation notes in the [compilation](./Compile.md) document.

If you are using gcc and a makefile, make sure you add a variable to supply the path to the root of your boost install

```bash
# Define library specific directories not expected to be in the environment paths
# Apple Mac M1 brew boost
BOOST_ROOT := "/opt/homebrew/Cellar/boost/1.79.0_1"

# Ubuntu/Mint Linux boost
BOOST_ROOT := "/usr/include/boost"
```

Then create a unit test file with the following information

```bash
#define BOOST_TEST_MODULE TEST_MODULE_NAME
#include <boost/test/included/unit_test.hpp>
```

The #define will provide scope for the tests and the #include brings in the unit test framework into the unit test file.  Once that is done, we just need to add a few unit tests.  This can be done by either [manually](https://www.boost.org/doc/libs/1_37_0/libs/test/doc/html/utf/user-guide/test-organization/manual-nullary-test-case.html) or [automatically](https://www.boost.org/doc/libs/1_37_0/libs/test/doc/html/utf/user-guide/test-organization/auto-nullary-test-case.html) registering the test.  Again more fun reading but lets just manually register for now by leveraging the BOOST_TEST_CASE macro.  The below example is pulled from the basic projects [unitTest_BasicMath.cpp](./project/tests/bin/unitTest_BasicMath.test) with the assumption that the #include "BasicMath.h" is present in the unit test source code.

```bash
/* Test known version */
BOOST_AUTO_TEST_CASE( get_version  )
{
    BOOST_CHECK_EQUAL (BasicMath::get_version(), 0.1);
}
```
The above example uses the BOOST_AUTO_TEST_CASE macro with the name get_version.  The BOOST_CHECK_EQUAL macro calls the method get_version() within BasicMath and asserts that it equals the value 0.1.  Any deviation from 0.1 will return a false or fail in the unit test.

Last but not least, we need to make it all go.  Since we are currently looking at makefiles, let's pull an example from the basic projects [Makefile](project/Makefile) where we created a test target just for this reason.

```bash
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
```

While this target gathers and compiles any .cpp file in the TESTS_DIRECTORY, it is the last line that calls each of the compiled unit test cases and formats and saves the logging output to a text file with output that will resemble the following.

```bash
[1;34;49mEntering test module "BasicMath"
[0;39;49m[1;34;49mtests/unitTest_BasicMath.cpp(7): Entering test case "get_version"
[0;39;49mtests/unitTest_BasicMath.cpp(9): [1;32;49minfo: check BasicMath::get_version() == 0.1 has passed[0;39;49m
[1;34;49mtests/unitTest_BasicMath.cpp(7): Leaving test case "get_version"; testing time: 258us
```

That in a nutshell is it.  Just a matter of research, rinse, and repeat.  I would highly recommend checking out the [Boost Test Library Documentation](https://www.boost.org/doc/libs/1_35_0/libs/test/doc/index.html), if for no other reason than to see what additional [macro options](https://www.boost.org/doc/libs/1_80_0/libs/config/doc/html/boost_config/boost_macro_reference.html) are provided.
