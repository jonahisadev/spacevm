#include <VM/Debugger.h>

namespace VM {

    Debugger::Debugger() {
        this->bpoints = new List<unsigned short>(1);
    }

    Debugger::~Debugger() {
        delete this->bpoints;
    }

    void Debugger::run(unsigned short addr, bool step) {
        if (!this->started) {
            printf(
                "SpaceVM Runtime Debugger\n"
                "Please set breakpoints, or run\n"
            );
        } else {
            if (!step)
                printf("Hit breakpoint 0x%04X\n", addr);

            // TODO: Print line
        }

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

        bool s = false;
        while (i < Util::strLength(cmd)) {
            lex[lexi++] = cmd[i++];

            // STARTED
            if (this->started) {
                if (Util::strEquals(lex, "step") ||
                        Util::strEquals(lex, "s")) {
                    this->modeStep = true;
                    s = true;
                    break;
                }

                if (Util::strEquals(lex, "continue") ||
                        Util::strEquals(lex, "c")) {
                    this->modeStep = false;
                    s = true;
                    break;
                }

            // NOT STARTED
            } else {
                if (tok == DebugToken::D_NONE) {
                    if (Util::strEquals(lex, "breakpoint") ||
                            Util::strEquals(lex, "bp")) {
                        tok = DebugToken::D_BPOINT;
                        i++;
                        s = true;
                        goto resetLex;
                    }
                    
                    if (Util::strEquals(lex, "run") ||
                            Util::strEquals(lex, "r")) {
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

            if (Util::strEquals(lex, "quit") ||
                    Util::strEquals(lex, "q")) {
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

    bool Debugger::isBreakpoint(unsigned short addr) {
        for (int i = 0; i < this->bpoints->getPointer(); i++) {
            if (this->bpoints->get(i) == addr)
                return true;
        }
        return false;
    }

} // namespace VM