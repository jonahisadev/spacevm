#ifndef SPACE_PARSER_H
#define SPACE_PARSER_H

#include <VM/Util.h>
#include <VM/Token.h>
#include <VM/Compiler.h>

namespace VM {

    class Parser {
    private:
        char* text;
		bool debug = false;
		int flen;
		
		bool nextPPI = false;
		int lastStoreSize = 0;
		
		TokenList* tokenList;
		List<char*>* lblList;
		List<char*>* jmpList;
		List<char*>* varList;
		List<char*>* addrList;

    public:
        Parser(char* text, int flen);
        ~Parser();

		void showTokenList();
		void showLabelLists();
		Compiler* createCompiler(const char* path);
		void ppi(char* inst);

        void setDebug(bool debug) { this->debug = debug; }
        inline bool isDebug() const { return debug; }

        void start();
		int checkInst(char* lex);
    };

} // namespace VM

#endif // SPACE_PARSER_H