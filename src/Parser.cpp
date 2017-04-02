#include <VM/Parser.h>

namespace VM {

    Parser::Parser(char* text) {
        this->text = text;
		this->tokenList = new TokenList(1);
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
		int line = 1;

        // Reset the buffer
        resetLex:
        for (int x = 0; x < 256; x++)
            lex[x] = '\0';
		lexi = 0;

        // Count up until delimeter is reached
        while (text[i] != '\n' && text[i] != '\0' && text[i] != delim) {
			lex[lexi++] = text[i++];
        }

        // Set the delimeter to nothing
        lex[lexi] = '\0';
		i++;

        // INSTRUCTIONS
        if (Util::strEquals(lex, "mov")) {
            tokenList->add(new Token(TokenType::INST, TokenInst::MOV));
        }
		else if (Util::strEquals(lex, "add")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::ADD));
		}
		else if (Util::strEquals(lex, "sub")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::SUB));
		}
		else if (Util::strEquals(lex, "call")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::CALL));
		}
		else if (Util::strEquals(lex, "ret")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::RET));
		}
		else if (Util::strEquals(lex, "sysi")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::SYSI));
		}
		else if (Util::strEquals(lex, "mul")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::MUL));
		}
		else if (Util::strEquals(lex, "div")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::DIV));
		}
		else if (Util::strEquals(lex, "sxr")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::SXR));
		}
		else if (Util::strEquals(lex, "sxl")) {
			tokenList->add(new Token(TokenType::INST, TokenInst::SXL));
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
			std::cerr << "Syntax Error (" << line << ") : " << lex << std::endl;
			panic("Aborting");
		}

		// Line for debugging
		if (text[i-1] == '\n')
			line++;

		// Check for EOF
		if (text[i-1] != '\0')
			goto resetLex;
    }

	void Parser::showTokenList() {
		this->tokenList->showList();
	}

	Compiler* Parser::createCompiler(const char* path) {
		return new Compiler(path, this->tokenList);
	}

} // namespace VM