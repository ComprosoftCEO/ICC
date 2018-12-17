# ICC
Insanity to C Compiler

<br/>

## About
Insanity is an [Esoteric Programming Language](https://en.wikipedia.org/wiki/Esoteric_programming_language) that I designed. All commands consist of single symbols (such as $, @, #, \*, etc). Although I already wrote an [Insanity interpreter in C](https://www.github.com/ComprosoftCEO/Insanity), the purpose of this project is to provide a "compiler" that converts an Insanity program to native machine code. But unlike a traditional compiler, which outputs machine code (or assembly code), the Insanity to C Compiler converts an Insanity program to C code. I did this for several reasons:
1. C compilers exist for almost any platform, so by extension Insanity can also be compiled on any platform.
2. Modern-day compilers can perform many code optimizations when converting to machine code.
3. Having C-linkage means that Insanity programs can easily compile to shared libraries for producing reusable Insanity code. This also allows the creation of Native insanity libraries (for features such as threads, file I/O, etc.) without having to build these features directly into Insanity.

<br/>

## Compiling ICC
The provided makefile should handle all of the compiling and linking of objects. However, you need to install the [Flex Lexer](https://www.gnu.org/software/flex/) and the [Bison Parser](https://www.gnu.org/software/bison/), as ICC uses Flex and Bison to generate the parser. For Debian distros, this is as simple as:
```
sudo apt-get install flex
sudo apt-get install bison
```

<br/>

## Usage
ICC \<InputFile\> \[OutFile\]
* __InputFile__ - The Insanity file to compile to C code. Insanity files generally have a __.ins__ extension.
* __OutFile (Optional)__ - File to use for writing the C code. By default, ICC outputs to __\<InputFile\>.c__

Note: While you should be able to compile the C files using any C compiler, Insanity uses [pointers to labels](https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html) for handling certain features in the code. Although this feature is supported by GCC, not all compilers may support this.

<br/>

## External Library Calls (Extension)
Unlike the [original Insanity interpreter](https://www.github.com/ComprosoftCEO/Insanity), ICC adds support for external labels and library calls. By default, an Insanity program is compiled to run with an `int main()` function in C. However, if an Insanity file has at least one external label, it is instead treated as a shared object. This means that the C code must be compiled to a .o file (and not an executable). Multiple .o files can be linked together to provide external calls to multiple files, or create a C shared library that can be used by other Insanity programs.

<br/>

## Native Library Development
Native shared libraries can be written for Insantiy to provide additional features not included in the languages (such as threading, file I/O, operating system calls, etc.). All files needed for native library development are stored in the `dev/` folder
* __Insanity-Dev.h__ - All macro and structure definitions for reading Insanity data. Also includes some helper functions.
* __Insanity-Dev.c__ (Optional) - Function implementations for helper functions. Only include this file if you intend to use these functions.

<br/>

The Insanity-Dev.h header defines the following structures:
* __Insanity_t__ - Data used by native Insanity programs. When writing you C code, PLEASE DO NOT attempt to corrupt this structure (such as writing invalid values into the Accumulator).
* __LibraryData_t__ - Used for storing library-specific data, if you library function needs to store data between invocations. 

<br/>

As of right now, the following helper functions are defined:
```c
//Get library specific data using a pre-defined string
void* getData(pInsanity_t insanity, const char* library);

//Set library specific data using a pre-defined string
void setData(pInsanity_t insanity, const char* library, void* data);
```

<br/>

Insanity functions should have the following prototype:
```c
bool myMethod(pInsanity_t insanity);
```
If the function returns `false`, then the Insanity program will terminate after returning from the method.

<br/>

To expose a function to Insanity, be sure to use the additional macro `INSANITY_METHOD(name,toCall)`. The `name` parameter specifies what should be in the \<Label\> part of an external library call, and the `toCall` parameter specifies what local C function to call.  Here is an example sample of code:
```c
//Method.c
#include <Insanity-Dev.h>

static bool myMethod(pInsanity_t insanity) {
  // Do some stuff...
  return true;
}

//Define public Insanity methods
INSANITY_METHOD(Method,myMethod);
```
```c
//Method.ins
[{Method}]
```

<br/>
<br/>

## Insanity Programming Language
To read about writing programs for Insanity, please check out the official [language definition](Insanity.md).
