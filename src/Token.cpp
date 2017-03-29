#include <VM/Token.h>

namespace VM {

	//
	//	TOKEN
	//

	Token::Token(TokenType type, int data) {
		this->type = type;
		this->data = data;
	}

	Token::~Token() {
		// Nothing
	}

	const char* Token::getInstruction(int inst) {
		switch (inst) {
			case TokenInst::MOV:
				return "MOV";
			case TokenInst::ADD:
				return "ADD";
		}
	}

	const char* Token::getRegister(int reg) {
		switch (reg) {
			case TokenReg::AX:
				return "%AX";
			case TokenReg::BX:
				return "%BX";
		}
	}

	int Token::getRegToken(char* reg) {
		if (Util::strEquals(reg, "%ax"))
			return TokenReg::AX;
		else if (Util::strEquals(reg, "%bx"))
			return TokenReg::BX;
		else {
			std::cerr << "Invalid register: " << reg << std::endl;
			panic("Aborting");
		}
	}

	//
	//	TOKEN LIST
	//

	TokenList::TokenList(int size) {
		this->data = (Token**) malloc(sizeof(Token*) * size);
		this->ptr = 0;
		this->size = size;
	}

	TokenList::~TokenList() {
		for (int i = 0; i < this->ptr; i++) {
			delete this->data[i];
		}
		free(this->data);
	}

	void TokenList::add(Token* t) {
		if (this->ptr >= this->size) {
			this->size *= 2;
			this->data = (Token**) realloc(this->data, sizeof(Token*) * this->size);
		}

		this->data[ptr++] = t;
	}

	Token* TokenList::get(int ptr) {
		return this->data[ptr];
	}

	void TokenList::showList() {
		Token* t;

		for (int i = 0; i < this->ptr; i++) {
			t = this->get(i);
			if (t->getType() == TokenType::INST) {
				std::cout << Token::getInstruction(t->getData()) << std::endl;
				continue;
			} else if (t->getType() == TokenType::REG) {
				std::cout << Token::getRegister(t->getData()) << std::endl;
				continue;
			}
		}
	}

} // namespace VM