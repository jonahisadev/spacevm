#include <VM/Debugger.h>

namespace VM {

    Debugger::Debugger() {
        this->bpoints = new List<unsigned short>(1);
    }

    Debugger::~Debugger() {
        delete this->bpoints;
    }
	
	void Debugger::begin() {
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

} // namespace VM