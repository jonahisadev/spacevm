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

    public:
        Debugger();
        ~Debugger();

        void begin();
    };

} // namespace VM

#endif // SPACE_DEBUGGER_H