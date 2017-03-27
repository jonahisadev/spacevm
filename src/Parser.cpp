#include <VM/Parser.h>

namespace VM {
    
    Parser::Parser(char* text) {
        this->text = text;
    }
    
    Parser::~Parser() {
        delete[] this->text;
    }
    
    void Parser::start() {
        char lex[256];
        int lexi;
        int i = 0;
        char delim = ' ';
        
        // Reset the buffer
        resetLex:
        for (int i = 0; i < 256; i++)
            lex[i] = '\0';
        
        // Count up until delimeter is reached
        while (lex[lexi] != delim) {
            lexi++;
        }
        
        // Set the delimeter to nothing
        lex[lexi] = '\0';
        
        // Check against instructions
        if (Util::strEquals("mov", lex)) {
            // TODO: Do this
        }
    }
    
} // namespace VM