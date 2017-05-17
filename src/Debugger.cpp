#include <VM/Debugger.h>

namespace VM {

    Debugger::Debugger(unsigned char* data) {
        this->data = data;
        this->bpoints = new List<unsigned short>(1);
        this->initInstMap();
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

            printLine(addr);
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
    
    void Debugger::printLine(unsigned short addr) {
        char* name = this->instMap->getName(this->data[addr]);
        printf("\n0x%04X: %s\n", addr, name);
    }

    bool Debugger::isBreakpoint(unsigned short addr) {
        for (int i = 0; i < this->bpoints->getPointer(); i++) {
            if (this->bpoints->get(i) == addr)
                return true;
        }
        return false;
    }
    
    //
    //  SPAMMY STUFF
    //
    
    void Debugger::initInstMap() {
        instMap->add(0x00, (char*)"NOP", 0);
        
        instMap->add(0x01, (char*)"MOV", 2);
        instMap->add(0x02, (char*)"MOV", 2);
        instMap->add(0x03, (char*)"MOV", 3);
        
        instMap->add(0x04, (char*)"ADD", 2);
        instMap->add(0x05, (char*)"ADD", 2);
        
        instMap->add(0x07, (char*)"SUB", 2);
        instMap->add(0x08, (char*)"SUB", 2);
        
        instMap->add(0x0A, (char*)"CALL", 2);
        instMap->add(0x0B, (char*)"RET", 0);
        instMap->add(0x0C, (char*)"SYSI", 0);
        
        instMap->add(0x10, (char*)"MUL", 2);
        instMap->add(0x11, (char*)"MUL", 2);
        
        instMap->add(0x13, (char*)"DIV", 2);
        instMap->add(0x14, (char*)"DIV", 2);
        
        instMap->add(0x16, (char*)"SXR", 1);
        instMap->add(0x17, (char*)"SXL", 1);
        instMap->add(0x18, (char*)"INC", 1);
        instMap->add(0x19, (char*)"DEC", 1);
        
        instMap->add(0x1A, (char*)"PUSH", 1);
        instMap->add(0x1B, (char*)"PUSH", 1);
        instMap->add(0x1C, (char*)"POP", 1);
        instMap->add(0x1D, (char*)"POP", 0);
        
        instMap->add(0x1E, (char*)"CMP", 2);
        instMap->add(0x1F, (char*)"CMP", 2);
        instMap->add(0x20, (char*)"JMP", 2);
        instMap->add(0x21, (char*)"JNE", 2);
        instMap->add(0x22, (char*)"JE", 2);
        instMap->add(0x23, (char*)"JG", 2);
        instMap->add(0x24, (char*)"JL", 2);
        instMap->add(0x25, (char*)"JGE", 2);
        instMap->add(0x26, (char*)"JLE", 2);
        instMap->add(0x27, (char*)"JZ", 2);
        instMap->add(0x28, (char*)"JNZ", 2);
        
        instMap->add(0x2A, (char*)"PUSHW", 1);
        instMap->add(0x2B, (char*)"PUSHW", 1);
        instMap->add(0x2C, (char*)"POPW", 1);
        instMap->add(0x2D, (char*)"POPW", 0);
        
        instMap->add(0x30, (char*)"AND", 2);
        instMap->add(0x31, (char*)"AND", 2);
        instMap->add(0x32, (char*)"OR", 2);
        instMap->add(0x33, (char*)"OR", 2);
        instMap->add(0x34, (char*)"XOR", 2);
        instMap->add(0x35, (char*)"XOR", 2);
        
        instMap->add(0x40, (char*)"HLT", 0);
        
        instMap->add(0x50, (char*)"PTR", 1);
        instMap->add(0x51, (char*)"PTR", 2);
        instMap->add(0x52, (char*)"STB", 1);
        instMap->add(0x53, (char*)"LDB", 3);
        instMap->add(0x54, (char*)"STW", 2);
        instMap->add(0x55, (char*)"LDW", 3);
        instMap->add(0x56, (char*)"STR", -1);
        
        instMap->add(0x60, (char*)"PUSHA", 0);
        instMap->add(0x61, (char*)"POPA", 0);
    }

} // namespace VM