#include <VM/Parser.h>

namespace VM {

    Parser::Parser(char* text, int flen) {
        this->text = text;
		this->flen = flen;
		this->tokenList = new TokenList(1);
		this->lblList = new List<char*>(1);
		this->jmpList = new List<char*>(1);
    }

    Parser::~Parser() {
        delete[] this->text;
    }

    void Parser::start() {
        char* lex = new char[256];
        int lexi;
        int i = 0;
        char delim = ' ';
		int line = 1;

        // Reset the buffer
        resetLex:
        for (int x = 0; x < 256; x++)
            lex[x] = '\0';
		lexi = 0;

		// Ignore empty lines
		if (text[i] == '\n') {
			i++;
			line++;
			goto resetLex;
		}

        // Count up until delimeter is reached
        while (text[i] != '\n' && text[i] != '\0' &&
				text[i] != delim && i < this->flen) {
			//if (text[i] == '\t')
				//i++; continue;
			lex[lexi++] = text[i++];
        }

        // Set the delimeter to nothing
        lex[lexi] = '\0';
		i++;

        // INSTRUCTIONS
		int tokenData;
		if ((tokenData = checkInst(lex)) != -1) {
			tokenList->add(new Token(TokenType::INST, tokenData));
		}

		// REGISTERS
		else if (lex[0] == '%') {
			tokenList->add(new Token(TokenType::REG, Token::getRegToken(lex)));
		}

		// NUMBERS
		else if (lex[0] == '#') {
			tokenList->add(new Token(TokenType::NUM, Token::convertNumber(lex)));
		}

		// LABELS
		else if (lex[0] == ':') {
			char* labelName = Util::strDup(lex, 1, Util::strLength(lex));
			// TODO: check for duplicates
			lblList->add(labelName);
			tokenList->add(new Token(TokenType::LBL, lblList->getPointer()-1));
		}
		else if (lex[0] == '@') {	
			char* jumpName = Util::strDup(lex, 1, Util::strLength(lex));
			jmpList->add(jumpName);
			tokenList->add(new Token(TokenType::JMP, jmpList->getPointer()-1));
		}

		// UNKNOWN
		else {
			std::cerr << "Syntax Error (" << line << ") : " << lex << std::endl;
			panic("Aborting");
		}

		if (i >= flen)
			return;

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
	
	void Parser::showLabelLists() {
		if (this->lblList->getPointer() > 0) {
			std::cout << "Label List: ";
			this->lblList->showList();
		}
		
		if (this->jmpList->getPointer() > 0) {
			std::cout << "Jump List: ";
			this->jmpList->showList();
		}
	}

	Compiler* Parser::createCompiler(const char* path) {
		return new Compiler(path, this->tokenList);
	}

	int Parser::checkInst(char* lex) {
		if (Util::strEquals(lex, "mov")) {
            return TokenInst::MOV;
        }
		else if (Util::strEquals(lex, "add")) {
			return TokenInst::ADD;
		}
		else if (Util::strEquals(lex, "sub")) {
			return TokenInst::SUB;
		}
		else if (Util::strEquals(lex, "call")) {
			return TokenInst::CALL;
		}
		else if (Util::strEquals(lex, "ret")) {
			return TokenInst::RET;
		}
		else if (Util::strEquals(lex, "sysi")) {
			return TokenInst::SYSI;
		}
		else if (Util::strEquals(lex, "mul")) {
			return TokenInst::MUL;
		}
		else if (Util::strEquals(lex, "div")) {
			return TokenInst::DIV;
		}
		else if (Util::strEquals(lex, "sxr")) {
			return TokenInst::SXR;
		}
		else if (Util::strEquals(lex, "sxl")) {
			return TokenInst::SXL;
		}
		else if (Util::strEquals(lex, "inc")) {
			return TokenInst::INC;
		}
		else if (Util::strEquals(lex, "dec")) {
			return TokenInst::DEC;
		}
		else if (Util::strEquals(lex, "push")) {
			return TokenInst::PUSH;
		}
		else if (Util::strEquals(lex, "pop")) {
			return TokenInst::POP;
		}

		else if (Util::strEquals(lex, "hlt")) {
			return TokenInst::HLT;
		}

		else {
			return -1;
		}
	}

} // namespace VM