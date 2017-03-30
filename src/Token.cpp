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

	int Token::convertNumber(char* str) {
		char* nStr = Util::strDup(str, 1, Util::strLength(str));
		int x = (int) strtol(nStr, (char**)NULL, 10);
		return x;
	}

	int Token::getRegToken(char* reg) {
		if (Util::strEquals(reg, "%ax"))
			return TokenReg::AX;
		else if (Util::strEquals(reg, "%bx"))
			return TokenReg::BX;
		else {
			std::cerr << "Invalid Register: " << reg << std::endl;
			panic("Aborting");
			return -1; // needed for clean compile
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
			} else if (t->getType() == TokenType::REG) {
				std::cout << Token::getRegister(t->getData()) << std::endl;
			} else if (t->getType() == TokenType::NUM) {
				std::cout << t->getData() << std::endl;
			}
		}
	}

	//
	//	SPAMMY STUFF
	//

	const char* Token::getInstruction(int inst) {
		switch (inst) {
			case TokenInst::MOV:
				return "MOV";
			case TokenInst::ADD:
				return "ADD";
			default:
				return "???";
		}
	}

	const char* Token::getRegister(int reg) {
		switch (reg) {
			case TokenReg::AX:
				return "%AX";
			case TokenReg::BX:
				return "%BX";
			case TokenReg::CX:
				return "%CX";
			case TokenReg::DX:
				return "%DX";
			case TokenReg::XX:
				return "%XX";
			case TokenReg::YX:
				return "%YX";
			case TokenReg::AL:
				return "%AL";
			case TokenReg::BL:
				return "%BL";
			case TokenReg::CL:
				return "%CL";
			case TokenReg::DL:
				return "%DL";
			case TokenReg::XL:
				return "%XL";
			case TokenReg::YL:
				return "%YL";
			case TokenReg::AH:
				return "%AH";
			case TokenReg::BH:
				return "%BH";
			case TokenReg::CH:
				return "%CH";
			case TokenReg::DH:
				return "%DH";
			case TokenReg::XH:
				return "%XH";
			case TokenReg::YH:
				return "%YH";
			case TokenReg::CF:
				return "%CF";
			case TokenReg::CY:
				return "%CY";
			case TokenReg::BP:
				return "%BP";
			case TokenReg::SP:
				return "%SP";
			case TokenReg::RM:
				return "%RM";
			default:
				return "%??";
		}
	}

} // namespace VM