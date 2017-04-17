# SpaceVM

### Description

A simple virtual machine compiler/runtime. Made by a high school student,
so it probably sucks a lot in terms of efficiency. The hope is to make it
functional first (with a framework for speed), and then rebuild bits and
pieces to make it better. The original idea for this project was to create
a VM for a game that would include system level programming. As the registers
and whatnot for this project are 16-bit, this isn't practically fit for
common usage, or for a language to be implemented in. This project may be
used for reference in the creation of a new VM in the future, fit more
for practical application.

### Dev Notes

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

* Implement high/low register access
* Allow file inclusion
* Make a debugger for runtime
* Sub-labels?
* Implement more system calls

### System Calls

* 0x01 - exit(code)
* 0x02 - print_b(byte)
* 0x03 - print_c(char)
* 0x04 - print_w(word)