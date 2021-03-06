#include <VM/Parser.h>

namespace VM {

    Parser::Parser(char* text, int flen) {
        this->text = text;
		this->flen = flen;
		this->tokenList = new TokenList(1);
		this->lblList = new List<char*>(1);
		this->jmpList = new List<char*>(1);
		this->varList = new List<char*>(1);
		this->addrList = new List<char*>(1);
		this->strList = new List<char*>(1);
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

		// Reserve Byte Number
		bool resNum = false;

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
			if (text[i] == '\t') {
				i++;
				continue;
			}
			
			if (text[i] == ';') {
				while (text[i] != '\n' && text[i] != '\0')
					i++;
				continue;
			}
			
			if (text[i] == '"') {
				delim = '"';
			}
			
			lex[lexi++] = text[i++];
        }
		
		// String?
		if (delim == '"') {
			delim = ' ';
			lex[lexi] = '"';
			lexi++;
		}

        // Set the delimeter to nothing
        lex[lexi] = '\0';
		i++;
		
		// Ignore lines filled with white-space
		bool empty = true;
		for (int j = 0; j < Util::strLength(lex); j++) {
			if (!isspace(lex[j]))
				empty = false; break;
		}
		if (empty) {
			line++;
			goto resetLex;
		}
			
		// Preprocessor check
		if (nextPPI) {
			ppi(lex, line);
			goto finalChecks;
		}

		int tokenData;	// used later
		
		// REGISTERS
		if (lex[0] == '%') {
			tokenList->add(new Token(TokenType::REG, Token::getRegToken(lex, line), line));
		}

		// NUMBERS
		else if (lex[0] == '$') {
			int num = Util::convertTokNum(lex, 10);
			tokenList->add(new Token(TokenType::NUM, num, line));
			if (resNum) {
				tokenList->get(tokenList->getPointer()-2)->setData(num);
				resNum = false;
			}
		}
		else if (lex[0] == '0' && lex[1] == 'x') {
			tokenList->add(new Token(TokenType::NUM, Util::convertTokNum(lex, 16), line));
		}

		// LABELS
		else if (lex[Util::strLength(lex)-1] == ':') {
			char* labelName = Util::strDup(lex, 0, Util::strLength(lex)-1);
			bool exists = false;
			for (int n = 0; n < lblList->getPointer(); n++) {
				if (Util::strEquals(labelName, lblList->get(n))) {
					exists = true;
					break;
				}
			}
			if (!exists) {
				lblList->add(labelName);
				tokenList->add(new Token(TokenType::LBL, lblList->getPointer()-1, line));
			} else {
				std::cerr << "Duplicate label (" << line << ") : " << labelName << std::endl;
				panic("Aborting");
			}
		}
		else if (lex[0] == '@') {	
			char* jumpName = Util::strDup(lex, 1, Util::strLength(lex));
			jmpList->add(jumpName);
			tokenList->add(new Token(TokenType::JMP_T, jmpList->getPointer()-1, line));
		}
		
		// VARIABLES
		else if (lex[0] == '&') {
			char* addr = Util::strDup(lex, 1, Util::strLength(lex));
			addrList->add(addr);
			tokenList->add(new Token(TokenType::ADDR, addrList->getPointer()-1, line));
		}
		else if (lex[0] == '*') {
			char* var = Util::strDup(lex, 1, Util::strLength(lex));
			varList->add(var);
			if (tokenList->get(tokenList->getPointer()-1)->getData() == TokenInst::STR) {
				tokenList->add(new Token(TokenType::VAR, 0, line));
			} else if (tokenList->get(tokenList->getPointer()-1)->getData() == TokenInst::RESB) {
				tokenList->add(new Token(TokenType::VAR, 0, line));
				resNum = true;
			} else {
				tokenList->add(new Token(TokenType::VAR, lastStoreSize, line));
			}
		}
		
		// STRINGS
		else if (lex[0] == '"' && lex[Util::strLength(lex)-1] == '"') {
			char* str = Util::strDup(lex, 1, Util::strLength(lex)-2);
			strList->add(str);
			tokenList->get(tokenList->getPointer()-1)->setData(Util::strLength(str)+1);		// update storeSize
			tokenList->add(new Token(TokenType::STRING, strList->getPointer()-1, line));
		}
		
		// PREPROCESSORS
		else if (lex[0] == '#') {
			char* inst = Util::strDup(lex, 1, Util::strLength(lex));
			ppi(inst, line);
		}
		
		// INSTRUCTIONS
		else if ((tokenData = checkInst(lex)) != -1) {
			tokenList->add(new Token(TokenType::INST, tokenData, line));
			if (tokenData == TokenInst::STB)
				lastStoreSize = 1;
			else if (tokenData == TokenInst::STW)
				lastStoreSize = 2;
		}

		// UNKNOWN
		else {
			std::cerr << "Syntax Error (" << line << ") : " << lex << std::endl;
			panic("Aborting");
		}

		finalChecks:
		// Backup check for EOF
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
		Compiler* c = new Compiler(path, this->tokenList);
		c->setLabelList(this->lblList);
		c->setJumpList(this->jmpList);
		c->setAddrList(this->addrList);
		c->setVarList(this->varList);
		c->setStrList(this->strList);
		c->setBeginLabel(this->beginLabel);
		c->setSymbols(this->symbols);
		return c;
	}
	
	void Parser::ppi(char* inst, int line) {
		if (!nextPPI) {
			if (Util::strEquals(inst, "data")) {
				tokenList->add(new Token(TokenType::PPI, TokenPPI::DATA, line));
			} 
			else if (Util::strEquals(inst, "end")) {
				tokenList->add(new Token(TokenType::PPI, TokenPPI::END, line));
			}
			else if (Util::strEquals(inst, "entry")) {
				tokenList->add(new Token(TokenType::PPI, TokenPPI::ENTRY, line));
				nextPPI = true;
			}
			else if (Util::strEquals(inst, "include")) {
				tokenList->add(new Token(TokenType::PPI, TokenPPI::INCLUDE, line));
				nextPPI = true;
			}
			else {
				std::cerr << "Invalid Preprocessor: '" << inst << "'" << std::endl;
				panic("Aborting");
			}
		} else {
			Token* lastToken = tokenList->get(tokenList->getPointer()-1);
			if (lastToken->getData() == TokenPPI::ENTRY) {
				this->beginLabel = const_cast<const char*>(Util::strDupFull(inst));
			}
			else if (lastToken->getData() == TokenPPI::INCLUDE) {
				includeFile(inst);
			}
			nextPPI = false;
		}
	}
	
	void Parser::includeFile(char* file) {
		// Parse
		char* path = Util::strDup(file, 1, Util::strLength(file)-2);
		char* fileContents = VM::Util::readFile(path);
		int flen = VM::Util::strLength(fileContents);
		ASSERT(fileContents, "File reading failure");
		Parser* subParser = new Parser(fileContents, flen);
		subParser->start();
		
		// Save offsets
		int tokenSize = tokenList->getPointer();
		int lblSize = lblList->getPointer();
		int jmpSize = jmpList->getPointer();
		int addrSize = addrList->getPointer();
		int strSize = strList->getPointer();
		
		// Append data
		this->tokenList->appendList(subParser->tokenList);
		this->lblList->appendList(subParser->lblList);
		this->jmpList->appendList(subParser->jmpList);
		this->varList->appendList(subParser->varList);
		this->addrList->appendList(subParser->addrList);
		this->strList->appendList(subParser->strList);
		
		// Correct included pointers
		for (int i = tokenSize-1; i < this->tokenList->getPointer(); i++) {
			Token* t = this->tokenList->get(i);
			if (t->getType() == TokenType::LBL)
				t->setData(t->getData() + lblSize);
			else if (t->getType() == TokenType::JMP_T)
				t->setData(t->getData() + jmpSize);
			else if (t->getType() == TokenType::ADDR)
				t->setData(t->getData() + addrSize);
			else if (t->getType() == TokenType::STRING)
				t->setData(t->getData() + strSize);
		}
	}

	int Parser::checkInst(char* lex) {
		Util::toCaps(lex);
		
		if (Util::strEquals(lex, "MOV"))
            return TokenInst::MOV;
		else if (Util::strEquals(lex, "ADD"))
			return TokenInst::ADD;
		else if (Util::strEquals(lex, "SUB"))
			return TokenInst::SUB;
		else if (Util::strEquals(lex, "CALL"))
			return TokenInst::CALL;
		else if (Util::strEquals(lex, "RET"))
			return TokenInst::RET;
		else if (Util::strEquals(lex, "SYSI"))
			return TokenInst::SYSI;
		else if (Util::strEquals(lex, "MUL"))
			return TokenInst::MUL;
		else if (Util::strEquals(lex, "DIV"))
			return TokenInst::DIV;
		else if (Util::strEquals(lex, "SXR"))
			return TokenInst::SXR;
		else if (Util::strEquals(lex, "SXL"))
			return TokenInst::SXL;
		else if (Util::strEquals(lex, "INC"))
			return TokenInst::INC;
		else if (Util::strEquals(lex, "DEC"))
			return TokenInst::DEC;
		else if (Util::strEquals(lex, "PUSH"))
			return TokenInst::PUSH;
		else if (Util::strEquals(lex, "POP"))
			return TokenInst::POP;
		else if (Util::strEquals(lex, "CMP"))
			return TokenInst::CMP;
		else if (Util::strEquals(lex, "JMP"))
			return TokenInst::JMP;
		else if (Util::strEquals(lex, "JNE"))
			return TokenInst::JNE;
		else if (Util::strEquals(lex, "JE"))
			return TokenInst::JE;
		else if (Util::strEquals(lex, "JG"))
			return TokenInst::JG;
		else if (Util::strEquals(lex, "JL"))
			return TokenInst::JL;
		else if (Util::strEquals(lex, "JGE"))
			return TokenInst::JGE;
		else if (Util::strEquals(lex, "JLE"))
			return TokenInst::JLE;
		else if (Util::strEquals(lex, "JZ"))
			return TokenInst::JZ;
		else if (Util::strEquals(lex, "JNZ"))
			return TokenInst::JNZ;
		else if (Util::strEquals(lex, "PUSHW"))
			return TokenInst::PUSHW;
		else if (Util::strEquals(lex, "POPW"))
			return TokenInst::POPW;
		else if (Util::strEquals(lex, "AND"))
			return TokenInst::AND;
		else if (Util::strEquals(lex, "OR"))
			return TokenInst::OR;
		else if (Util::strEquals(lex, "XOR"))
			return TokenInst::XOR;
		else if (Util::strEquals(lex, "ARG"))
			return TokenInst::ARG;
		else if (Util::strEquals(lex, "ARGW"))
			return TokenInst::ARGW;
		else if (Util::strEquals(lex, "POPX"))
			return TokenInst::POPX;
		else if (Util::strEquals(lex, "PTR"))
			return TokenInst::PTR;
		else if (Util::strEquals(lex, "STB"))
			return TokenInst::STB;
		else if (Util::strEquals(lex, "LDB"))
			return TokenInst::LDB;
		else if (Util::strEquals(lex, "STW"))
			return TokenInst::STW;
		else if (Util::strEquals(lex, "LDW"))
			return TokenInst::LDW;
		else if (Util::strEquals(lex, "STR"))
			return TokenInst::STR;
		else if (Util::strEquals(lex, "RESB"))
			return TokenInst::RESB;
		else if (Util::strEquals(lex, "PUSHA"))
			return TokenInst::PUSHA;
		else if (Util::strEquals(lex, "POPA"))
			return TokenInst::POPA;
		else if (Util::strEquals(lex, "MOVW"))
			return TokenInst::MOVW;
		else if (Util::strEquals(lex, "ADDW"))
			return TokenInst::ADDW;
		else if (Util::strEquals(lex, "SUBW"))
			return TokenInst::SUBW;
		else if (Util::strEquals(lex, "MULW"))
			return TokenInst::MULW;
		else if (Util::strEquals(lex, "DIVW"))
			return TokenInst::DIVW;

		else if (Util::strEquals(lex, "HLT"))
			return TokenInst::HLT;

		else {
			return -1;
		}
	}

} // namespace VM