# C/C++ Basic Walk Through

## The Very Beginning - Main

Execution of a C/C++ program begins in the c file (typically .c for C and .cpp for C++) at the main function. Typically this function is itself called main, but the entry point can be changed with a bit of work (would not recommend it though) and if you are doing this, you know too much about C/C++ but little about control.  This function itself exist in a file called main but can live any file the developers choose.  If you are fortunate to enough to have to maintain this type of code and are looking for the main, try finding a file name that matches the program name.  This too is not always the case, which is why I generally recommend using a file named main, and you may have to just break down and do a recursive grep/search for the main function.  

Typically you will see the following function: 
```c++
int main(int argc, char *argv[])
{

}
```

The first variable, argc, contains the number of arguments passed in during the execution of the program while the variable argv[] contains an array of pointers to the values of  each of the arguments.  Additionally, the variable char *argv[] can also be represented as char **argv, which in this case is quite similar since the array is simply a collection of pointers to character pointers  (yeah, we'll discuss pointers later).

Being C/C++, the array is 0 referenced (first entry is at 0) with argv[0] containing the fully qualified path where the binary file was started.  Please note however that this path is not always where the binary itself currently resides, just where the command was issued from and on systems like UNIX, you may end up with the path to the symbolic link.

This being C/C++ and the number of compilers available, you will see some variation to the previous example.  In fact, IDE's such as Visual Studio's wizard will put their main functions in a file named after the solution/project/program with a main that looks like the following.  

```c++
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
```

While it looks similar, and in fact acts that same, this is strictly a Microsoft implementation and will generally not work with any other compile, whereas the original example should work everywhere.
