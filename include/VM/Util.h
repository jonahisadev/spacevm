#ifndef SPACE_UTIL_H
#define SPACE_UTIL_H

#include <cstdio>
#include <cstdlib>

namespace VM {
    
    class Util {
    public:
        static char* readFile(const char* path);   
    };
    
}

#endif // SPACE_UTIL_H