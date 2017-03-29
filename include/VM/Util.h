#ifndef SPACE_UTIL_H
#define SPACE_UTIL_H

#include <stdio.h>
#include <cstdlib>

#include <VM/Common.h>

namespace VM {

    class Util {
    public:
        LOCAL char* readFile(const char* path);
        LOCAL int strLength(const char* a);
        LOCAL bool strEquals(const char* a, const char* b);
    };

} // namespace VM

#endif // SPACE_UTIL_H