# SpaceVM

### Description

A simple virtual machine compiler/runtime. Made by a high school student,
so it probably sucks a lot in terms of efficiency. The hope is to make it
functional first (with a framework for speed), and then rebuild bits and
pieces to make it better.

### Dev Notes

For adding opcodes for the compiler, please have the following files open
in the following order:

* Token.h
* Token.cpp
* Parser.cpp
* Compiler.h
* Compiler.cpp

Obviously more things need to be implemented before the compiler will be
100% functional. Getting the opcodes in place for now will be busywork.

### To Do

* Finish writing compiler opcodes
* Try to fix number conversion problems
* Implement templating for list classes
* Make a debugger for runtime
* Ignore empty lines
* Add comments soon