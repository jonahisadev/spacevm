#ifndef SPACE_PARSER_H
#define SPACE_PARSER_H

#include <VM/Util.h>
#include <VM/Token.h>
#include <VM/Compiler.h>

namespace VM {

    class Parser {
    private:
        char* text;
		TokenList* tokenList;
		bool debug = false;

    public:
        Parser(char* text);
        ~Parser();

		void showTokenList();
		Compiler* createCompiler(const char* path);

        void setDebug(bool debug) { this->debug = debug; }
        inline bool isDebug() const { return debug; }

        void start();
		int checkInst(char* lex);
    };

} // namespace VM

#endif // SPACE_PARSER_H