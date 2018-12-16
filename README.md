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
<br/>

# Insanity Programming Language
Insanity is a programming language designed by Bryan McClain. Similar to assembly, Insanity uses single-symbol commands such as < + and $ to represent simple operations. All text characters that aren’t commands are ignored, unless part of a label or jump command. Whitespace (spacebar, tab, etc.) is ignored, even when inside a label. 

<br />

## System Architecture
---
### Registers
The Insanity programming language has 2 registers, the Accumulator and the Backup. The Accumulator is used for basic mathematical operations (addition and subtraction) as well as all of the compare operations (greater than, less than, etc.). The Backup register cannot be written to or read from directly, but can be accessed via the save and swap commands ($ and ~). Registers can hold values from -999 to 999 (inclusive).

<br/>

### Memory
Within the Insanity programming language are 1000 memory slots that can be written to and read from using the Accumulator. Like registers, memory slots can hold values between -999 and 999 (inclusive). Memory is navigated using the memory cursor (detailed below).

<br/>

### The Stack
One common feature of modern programming languages is the concept of subroutines. Insanity is no exception, and contains an internal stack for storing subroutines. The Insanity stack holds the last 100 calls to a subroutine, with a stack pointer indicating the current position in the stack. However, the values in the stack cannot be directly accessed within an Insanity program, and are handled by the implementation of Insanity. (The Insanity program itself only controls when subroutine or a return from subroutine is called). Errors should be thrown for stack overflow or underflow.

<br/>

### Status Flags
In addition to registers and memory, Insanity has two status flags that are used during execution. These flags are the Overflow Flag and the Compare Flag.
* The Overflow Flag is set to true when the result of an addition or subtraction operation results in a value greater than 999 or less than -999. If the operation is successful, then the Overflow Flag is set to false.
* The Compare Flag is set to true when the result of a compare operation is true, or false when the result of a compare operation is false.

<br/>

### Cursors
Finally, the Insanity programming language has two cursors used during execution. These cursors are called the Memory Cursor and the Digit Cursor. The cursors do not loop around.
* The Memory Cursor represents the currently “selected” memory slot. This is the memory slot that will be written to and read from using the Accumulator.
* The Digit Cursor represents the current digits spot. This cursor can be in one of three states: 1’s, 10’s, or 100’s. When performing addition or subtraction operations, the computer will add the respective value. (I.E. if the Digit Cursor is in the 10’s position, the computer will add and subtract the number 10) The digit cursor also indicates how many memory slots to move the memory cursor with the \< and \> commands.

<br/>
<br/>

## Commands
---
### Labels
Labels represent points in the code that the computer can jump to. Labels are identified by their unique name, consisting of letters and numbers. All other characters, including whitespace and commands, are ignored inside a label. <Label> represents this unique identifier. External labels expose entry points in the program for other Insanity code files.

| Command | Description |
| ------- | ----------- |
| :\<Label\>:   | Defines a label named \<Label\> |
| :{\<Label\>}: | Define an external label named \<Label\> |
| (\<Label\>)   | Jumps to the label named \<Label\> |
<br/>

### Subroutines
Subroutines are useful when you want to reuse sections of code by calling the code from different locations in the program. Insanity allows for a maximum of 100 nested Subroutine calls. Subroutine calls are handled by the Insanity implementation, and not by the program itself. External subroutine jumps allow the program to execute code in an external Insanity shared library.

| Command | Description |
| ------- | ----------- |
| [\<Label\>]   | Jumps to the Subroutine, storing the current location of the program in the stack |
| [{\<Label\>}] | Call an external Insanity function, defined by an external label in another Insanity file |
| ; | Return from the Subroutine by jumping to the location in the program indicated by the stack |
<br/>

### Cursors
| Command | Description |
| ------- | ----------- |
| > | Move the Memory Cursor 1 slot right based on the value of the memory cursor |
| < | Move the Memory Cursor 1 slot left based on the value of the digit cursor |
| \" | Increase the Digit Cursor by 1 digit (Multiply by 10) |
| \' | Decrease the Digit Cursor by 1 digit (Divide by 10) |
| \_ | Reset the value of the Memory Cursor and Digit Cursor |
<br/>

### Memory and Register Access
| Command | Description |
| ------- | ----------- |
| ^ | Upload the selected memory value to the Accumulator |
| \| | Swap the values of the Accumulator and the selected memory slot |
| $ | Save the value of the Accumulator to the Backup register |
| ~ | Swap the value of the Accumulator and Backup registers |
<br/>

### Arithmetic
| Command | Description |
| ------- | ----------- |
| + | Add 1 to the Accumulator based on the value of the Digit Cursor |
| - | Subtract 1 from the Accumulator based on the value of the Digit Cursor |
| & | Add the value of the Backup register to the Accumulator |
| \` | Negate the Accumulator (Multiply by -1) |
| @ | Reset the value of the Accumulator to 0 |
| % | Set the Accumulator to a random number from -999 to 999 |
<br/>

### Compare
| Command | Description |
| ------- | ----------- |
| = | Set the Compare Flag to true if the Accumulator is equal to 0 |
| * | Set the Compare Flag to true if the Accumulator is not equal to 0 |
| / | Set the Compare Flag to true if the Accumulator is greater than 0 |
| \ | Set the Compare Flag to true if the Accumulator is less than 0 |
| ! | Set the Compare Flag to true if the Overflow is true |
| {\<Code\>} | Execute the \<Code\> within the brackets if the Compare Flag is equal to true |
<br/>

### Input and Output
| Command | Description |
| ------- | ----------- |
| ? | Ask the user to input a number (-999 to 999). Store this number in the Accumulator |
| # | Output the value of the Accumulator as a text character (See Character Conversion Chart) |
<br/>

### Other
| Command | Description |
| ------- | ----------- |
| , | Pause the program (Used for debugging code) |
| . | End the program |

<br/>
<br />

## Character Conversion Chart
---
The Insanity programming language uses a custom Character Conversion Chart (similar to the ASCII table) for outputting characters. The character with its associated number are displayed in the following table:

| Number | Letter |   | Number | Letter |   | Number | Letter |   | Number | Letter |   | Number | Letter |
| ------ | ------ | - | ------ | ------ | - | ------ | ------ | - | ------ | ------ | - | ------ | ------ |
| 0 | (Space) | | 20 | 4 | | 40 | H | | 60 | \ | | 80 | P |
| 1 | ! | | 21 | 5 | | 41 | I | | 61 | ] | | 81 | Q |
| 2 | " | | 22 | 6 | | 42 | J | | 62 | ^ | | 82 | R |
| 3 | # | | 23 | 7 | | 43 | K | | 63 | _ | | 83 | S |
| 4 | $ | | 24 | 8 | | 44 | L | | 64 | \` | | 84 | T |
| 5 | % | | 25 | 9 | | 45 | M | | 65 | A | | 85 | U |
| 6 | \& | | 26 | : | | 46 | N | | 66 | B | | 86 | V |
| 7 | \' | | 27 | ; | | 47 | O | | 67 | C | | 87 | W |
| 8 | ( | | 28 | \< | | 48 | P | | 68 | D | | 88 | X |
| 9 | ) | | 29 | = | | 49 | Q | | 69 | E | | 89 | Y |
| 10 | * | | 30 | \> | | 50 | R | | 70 | F | | 90 | Z |
| 11 | + | | 31 | ? | | 51 | S | | 71 | G | | 91 | { |
| 12 | , | | 32 | @ | | 52 | T | | 72 | H | | 92 | \| |
| 13 | - | | 33 | A | | 53 | U | | 73 | I | | 93 | } |
| 14 | . | | 34 | B | | 54 | V | | 74 | J | | 94 | ~ |
| 15 | / | | 35 | C | | 55 | W | | 75 | K | | \>94 | ☺ |
| 16 | 0 | | 36 | D | | 56 | X | | 76 | L | | -1 | (Enter) |
| 17 | 1 | | 37 | E | | 57 | Y | | 77 | M | | <-1 | ☹ |
| 18 | 2 | | 38 | F | | 58 | Z | | 78 | N | | -999 | (Clear) |
| 19 | 3 | | 39 | G | | 59 | [ | | 79 | O | | | |

Note that numbers greater than 94 output a smiley face (☺) and numbers less than -1 output a sad face (☹). The number -1 starts a new line of text characters, and 0 is the space character. The number -999 clears all text.
