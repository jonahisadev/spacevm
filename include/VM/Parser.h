#ifndef SPACE_PARSER_H
#define SPACE_PARSER_H

#include <VM/Util.h>
#include <VM/Token.h>

namespace VM {

    class Parser {
    private:
        char* text;
		TokenList* tokenList;

    public:
        Parser(char* text);
        ~Parser();

		void showTokenList();

        void start();
    };

} // namespace VM

#endif // SPACE_PARSER_H