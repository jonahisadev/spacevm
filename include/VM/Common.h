#ifndef SPACE_COMMON_H
#define SPACE_COMMON_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

#define GLOBAL static
#define LOCAL static

#define ASSERT(x, y) \
    if (!(x)) panic(y);

GLOBAL void panic(const char* msg) {
    std::cerr << msg << std::endl;
    std::exit(1);
}

#endif // SPACE_COMMON_H