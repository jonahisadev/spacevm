#include <VM/Parser.h>

namespace VM {

    Parser::Parser(char* text) {
        this->text = text;
		this->tokenList = new TokenList(2);
    }

    Parser::~Parser() {
        delete[] this->text;
    }

    void Parser::start() {
        char lex[256];
        int lexi;
        int i = 0;
        char delim = ' ';
		int nextJump = 1;

        // Reset the buffer
        resetLex:
        for (int x = 0; x < 256; x++)
            lex[x] = '\0';
		lexi = 0;

        // Count up until delimeter is reached
        while (text[i] != delim && (text[i] != '\0' || text[i] == '\n')) {
			lex[lexi++] = text[i++];
        }

        // Set the delimeter to nothing
        lex[lexi] = '\0';
		i++;

        // INSTRUCTIONS
        if (Util::strEquals("mov", lex)) {
            tokenList->add(new Token(TokenType::INST, TokenInst::MOV));
        }

		// REGISTERS
		else if (lex[0] == '%') {
			tokenList->add(new Token(TokenType::REG, Token::getRegToken(lex)));
		}

		// NUMBERS
		else if (lex[0] == '#') {
			tokenList->add(new Token(TokenType::NUM, Token::convertNumber(lex)));
		}

		// UNKNOWN
		else {
			std::cerr << "Syntax Error: " << lex << std::endl;
			return;
			//panic("Aborting");
		}

		if (text[i] != '\0')
			goto resetLex;
    }

	void Parser::showTokenList() {
		this->tokenList->showList();
	}

	Compiler* Parser::createCompiler(const char* path) {
		return new Compiler(path, this->tokenList);
	}

} // namespace VM