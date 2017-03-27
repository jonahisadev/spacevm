#ifndef SPACE_UTIL_H
#define SPACE_UTIL_H

#include <stdio.h>
#include <cstdlib>

#include <VM/Common.h>

namespace VM {
    
    class Util {
    public:
        LOCAL char* readFile(CONST char* path);   
    };
    
} // namespace VM

#endif // SPACE_UTIL_H