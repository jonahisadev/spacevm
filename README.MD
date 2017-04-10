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
and debugging the current VM is priority along with the first couple of items

### To Do

* String support
* Make a debugger for runtime
* Implement more system calls

### Data Section Checklist

* Add Data section parsing
* Add STB opcode
* Add variable parsing
* Have a variable table for compilation
* Make it work yo