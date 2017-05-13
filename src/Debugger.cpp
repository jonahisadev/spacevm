#include <VM/Debugger.h>

namespace VM {

    Debugger::Debugger() {
        this->bpoints = new List<unsigned short>(1);
    }

    Debugger::~Debugger() {
        delete this->bpoints;
    }

    void Debugger::bp(unsigned short addr) {
        printf("Hit breakpoint 0x%04X\n", addr);
        char* cmd = new char[256];
        printf("dbg > ");
        fgets(cmd, 256, stdin);
    }
	
	void Debugger::begin() {
        printf(
            "SpaceVM Runtime Debugger\n"
            "Please set breakpoints, or run\n"
        );

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

        while (true) {
            lex[lexi++] = cmd[i++];

            if (tok == DebugToken::D_NONE) {
                if (Util::strEquals(lex, "breakpoint") ||
                        Util::strEquals(lex, "bp")) {
                    tok = DebugToken::D_BPOINT;
                    i++;
                    goto resetLex;
                }
                
                if (Util::strEquals(lex, "run") ||
                        Util::strEquals(lex, "r")) {
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
                    goto debugStart;
                }
            }
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