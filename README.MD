# SpaceVM

## Description

A simple virtual machine compiler/runtime. Made by a high school student,
so it probably sucks a lot in terms of efficiency. The hope is to make it
functional first (with a framework for speed), and then rebuild bits and
pieces to make it better. Once a big portion of this is finished, I will be
converting the whole system to 32-bit instead of 16-bit. Things will break.
It will be difficult. But it'll be fun, and it'll be awesome.

## Dev Notes

### Opcode Additions

For adding opcodes, please have the following files open in the following 
order:

* Token.h
* Token.cpp
* Parser.cpp
* Bytecode.h
* Compiler.cpp
* (Decomp.cpp)
* Runtime.cpp

To Do list is likely in the order of features to be added. As of now, testing
and debugging the current VM is priority along with the first couple of items.

### To Do

* Improve jumps/calls to labels
* Figure out a way to debug with file inclusions
* Implement high/low register access
* Maintain documentation
	* Add register list
	* Continue limitations
* Make a debugger for runtime
* Sub-labels?
* Implement more system calls

### System Calls

* 0x01 - exit(code)
* 0x02 - print_b(byte)
* 0x03 - print_c(char)
* 0x04 - print_w(word)