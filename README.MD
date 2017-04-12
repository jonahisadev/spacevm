# SpaceVM

### Description

A simple virtual machine compiler/runtime. Made by a high school student,
so it probably sucks a lot in terms of efficiency. The hope is to make it
functional first (with a framework for speed), and then rebuild bits and
pieces to make it better.

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

* Store words
* String support
* Make a debugger for runtime
* Sub-labels?
* Implement more system calls
* Allow file inclusion

### System Calls

* 0x01 - exit(code)
* 0x02 - print_b(byte)
* 0x03 - print_c(char)
* 0x04 - print_w(word)