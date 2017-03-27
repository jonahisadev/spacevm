#ifndef SPACE_COMMON_H
#define SPACE_COMMON_H

#include <iostream>
#include <cstdlib>

#define ASSERT(x, y) \
    if (!(x)) panic(y);
    
void panic(const char* msg) {
    std::cerr << msg << std::endl;
    std::exit(1);
}

#endif // SPACE_COMMON_H