#include <VM/Debugger.h>

namespace VM {

    Debugger::Debugger(Runtime* r, unsigned char* data) {
        this->data = data;
        this->bpoints = new List<unsigned short>(1);
        this->d = new Decomp(data, false, nullptr);
        this->r = r;
    }

    Debugger::~Debugger() {
        delete this->bpoints;
        delete this->d;
    }

    void Debugger::run(unsigned short addr, bool step) {
        if (!this->started) {
            printf(
                "SpaceVM Runtime Debugger\n"
                "Please set breakpoints, or run\n"
            );
        } else {
            if (!step) {
                printf("Hit breakpoint 0x%04X\n", addr);
            }

            printLine(addr);
        }
        
        bool s;

        debugStart:
        char* cmd = new char[256];
        printf("dbg > ");
        fgets(cmd, 256, stdin);
        cmd[Util::strLength(cmd)-1] = '\0';

        char* lex = new char[256];
        int lexi = 0;
        int i = 0;
        DebugToken tok = DebugToken::D_NONE;

        resetLex:
        lexi = 0;
        for (int x = 0; x < 255; x++)
            lex[x] = '\0';

        s = false;
        while (i < Util::strLength(cmd)) {
            lex[lexi++] = cmd[i++];

            // STARTED
            if (this->started) {
                if (tok == DebugToken::D_NONE) {
                    // STEP
                    if (Util::strEquals(cmd, "step") ||
                            Util::strEquals(cmd, "s")) {
                        this->modeStep = true;
                        s = true;
                        break;
                    }
    
                    // CONTINUE
                    else if (Util::strEquals(cmd, "continue") ||
                             Util::strEquals(cmd, "c")) {
                        this->modeStep = false;
                        s = true;
                        break;
                    }
                    
                    // REGISTERS
                    else if (Util::strEquals(cmd, "registers") ||
                             Util::strEquals(cmd, "reg")) {
                        this->r->printRegisters();
                        goto debugStart;
                    }
                    
                    // STACK FRAME
                    else if (Util::strEquals(lex, "stack") ||
                             Util::strEquals(lex, "sf")) {
                        tok = DebugToken::D_STACK;
                        i++;
                        s = true;
                        goto resetLex;
                    }
                } else if (tok == DebugToken::D_STACK) {
                    if (cmd[i] == '\0') {
                        lex[lexi] = '\0';
                        unsigned short addr = (unsigned short)Util::convertNum(lex, 16);
                        this->r->printStack(addr);
                        delete[] cmd;
                        delete[] lex;
                        s = true;
                        goto debugStart;
                    }
                }

            // NOT STARTED
            } else {
                if (tok == DebugToken::D_NONE) {
                    // BREAKPOINT
                    if (Util::strEquals(lex, "breakpoint") ||
                            Util::strEquals(lex, "bp")) {
                        tok = DebugToken::D_BPOINT;
                        i++;
                        s = true;
                        goto resetLex;
                    }
                    
                    // RUN
                    else if (Util::strEquals(cmd, "run") ||
                             Util::strEquals(cmd, "r")) {
                        s = true;
                        this->started = true;
                        break;
                    }
                } else if (tok == DebugToken::D_BPOINT) {
                    if (cmd[i] == '\0') {
                        lex[lexi] = '\0';
                        unsigned short addr = (unsigned short)Util::convertNum(lex, 16);
                        this->bpoints->add(addr);
                        printf("Breakpoint %d set to 0x%04X\n", this->bpoints->getPointer(), addr);
                        delete[] cmd;
                        delete[] lex;
                        s = true;
                        goto debugStart;
                    }
                }
            }

            if (Util::strEquals(cmd, "quit") ||
                    Util::strEquals(cmd, "q")) {
                std::exit(0);
            }
        }

        if (!s) {
            printf("Invalid command\n");
            delete[] cmd;
            delete[] lex;
            goto debugStart;
        }

        delete[] cmd;
        delete[] lex;
    }
    
    void Debugger::printLine(unsigned short addr) {
        printf("\t\t");
        this->d->hijack(&addr);
        this->d->start();
    }

    bool Debugger::isBreakpoint(unsigned short addr) {
        for (int i = 0; i < this->bpoints->getPointer(); i++) {
            if (this->bpoints->get(i) == addr)
                return true;
        }
        return false;
    }

} // namespace VM