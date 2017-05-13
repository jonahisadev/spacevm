#ifndef SPACE_DEBUGGER_H
#define SPACE_DEBUGGER_H

#include <VM/Util.h>
#include <VM/List.h>

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
        bool modeStep = false;
        bool started = false;

    public:
        Debugger();
        ~Debugger();

        bool isBreakpoint(unsigned short addr);
        void run(unsigned short addr, bool step);
        inline bool isModeStep() { return modeStep; }
    };

} // namespace VM

#endif // SPACE_DEBUGGER_H