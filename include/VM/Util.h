#ifndef SPACE_UTIL_H
#define SPACE_UTIL_H

#include <stdio.h>
#include <cstdlib>

#include <VM/Common.h>

namespace VM {

    class Util {
    public:
        LOCAL char* readFile(const char* path);
		LOCAL unsigned char* readBinFile(const char* path);
        LOCAL int strLength(const char* a);
        LOCAL bool strEquals(const char* a, const char* b);
        LOCAL void strCopy(char* src, char* dest, int start, int end);
        LOCAL char* strDup(char* src, int start, int end);
		LOCAL char* strDupFull(char* src);
		LOCAL unsigned char* sToB(unsigned short addr);
		LOCAL unsigned short bToS(unsigned char a, unsigned char b);
    };

} // namespace VM

#endif // SPACE_UTIL_H