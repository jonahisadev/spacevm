#ifndef SPACE_DEBUGGER_H
#define SPACE_DEBUGGER_H

#include <VM/Util.h>
#include <VM/List.h>
#include <VM/Decomp.h>

#include <iostream>
#include <cstdio>

namespace VM {

    enum class DebugToken {
        D_NONE,
        D_BPOINT,
    };

    class Debugger {
    private:
        List<unsigned short>* bpoints;
        Decomp* d;
        
        bool modeStep = false;
        bool started = false;
        
        unsigned char* data;

    public:
        Debugger(unsigned char* data);
        ~Debugger();

        bool isBreakpoint(unsigned short addr);
        void run(unsigned short addr, bool step);
        inline bool isModeStep() { return modeStep; }
        void printLine(unsigned short addr);
    };

} // namespace VM

#endif // SPACE_DEBUGGER_H