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

* Add data section
* String support
* Make a debugger for runtime
* Implement more system calls

### The First Six Bytes

Just for some personal documentation on the first six bytes of the program:
Why are they there? They're actually two sets of three bytes, which will
contain a call and a jump. The first byte will be the call instruction. The next
two will be an address. That address will be the section of the bytecode that
will set up the "data" section of the code: all of the variables. A return
instruction will be placed at the end of the section during compilation. Once
returned, there will be a jump instruction to the "start" label, if any. These
six bytes are completely optional to the source code, but if a data section
or a start label are included in source, the respective bytes *must* be set