#ifndef SPACE_DEBUGGER_H
#define SPACE_DEBUGGER_H

#include <VM/Util.h>
#include <VM/List.h>

#include <iostream>
#include <cstdio>

namespace VM {

    typedef struct InstMap_ {
        List<unsigned char>*    code = new List<unsigned char>(1);
        List<char*>*            name = new List<char*>(1);
        List<unsigned char>*    args = new List<unsigned char>(1);
        
        void add(unsigned char code, char* name, unsigned char args) {
            this->code->add(code);
            this->name->add(Util::strDupFull(name));
            this->args->add(args);
        }

        char* getName(unsigned char inst) {
            for (int i = 0; i < this->code->getPointer(); i++) {
                if (inst == this->code->get(i)) {
                    return this->name->get(i);
                }
            }
            return nullptr;
        }
    } InstMap;

    enum class DebugToken {
        D_NONE,
        D_BPOINT,
    };

    class Debugger {
    private:
        List<unsigned short>* bpoints;
        InstMap* instMap = new InstMap();
        
        bool modeStep = false;
        bool started = false;
        
        unsigned char* data;
        
        void initInstMap();

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