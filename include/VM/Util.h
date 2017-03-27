#ifndef SPACE_UTIL_H
#define SPACE_UTIL_H

#include <stdio.h>
#include <cstdlib>

#include <VM/Common.h>

namespace VM {
    
    class Util {
    public:
        LOCAL char* readFile(CONST char* path);
        LOCAL int strLength(char* a);
        LOCAL bool strEquals(char* a, char* b);
    };
    
} // namespace VM

#endif // SPACE_UTIL_H