#include <VM/Token.h>

namespace VM {

	//
	//	TOKEN
	//

	Token::Token(TokenType type, int data, int line) {
		this->type = type;
		this->data = data;
		this->line = line;
	}

	Token::~Token() {
		// Nothing
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
	
	void TokenList::appendList(TokenList* list) {
		for (int i = 0; i < list->getPointer(); i++) {
			this->add(list->get(i));
		}
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
			} else if (t->getType() == TokenType::LBL) {
				std::cout << "Label: i" << t->getData() << std::endl;
			} else if (t->getType() == TokenType::JMP_T) {
				std::cout << "JumpTo: i" << t->getData() << std::endl;
			} else if (t->getType() == TokenType::PPI) {
				std::cout << "PPI: " << t->getData() << std::endl;
			} else if (t->getType() == TokenType::VAR) {
				std::cout << "VAR: " << t->getData() << std::endl;
			} else if (t->getType() == TokenType::STRING) {
				std::cout << "STR: " << t->getData() << std::endl;
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
			case TokenInst::SUB:
				return "SUB";
			case TokenInst::CALL:
				return "CALL";
			case TokenInst::RET:
				return "RET";
			case TokenInst::SYSI:
				return "SYSI";
			case TokenInst::MUL:
				return "MUL";
			case TokenInst::DIV:
				return "DIV";
			case TokenInst::SXR:
				return "SXR";
			case TokenInst::SXL:
				return "SXL";
			case TokenInst::HLT:
				return "HLT";
			case TokenInst::INC:
				return "INC";
			case TokenInst::DEC:
				return "DEC";
			case TokenInst::PUSH:
				return "PUSH";
			case TokenInst::POP:
				return "POP";
			case TokenInst::CMP:
				return "CMP";
			case TokenInst::JMP:
				return "JMP";
			case TokenInst::JNE:
				return "JNE";
			case TokenInst::JE:
				return "JE";
			case TokenInst::JG:
				return "JG";
			case TokenInst::JL:
				return "JL";
			case TokenInst::JGE:
				return "JGE";
			case TokenInst::JLE:
				return "JLE";
			case TokenInst::JZ:
				return "JZ";
			case TokenInst::JNZ:
				return "JNZ";
			case TokenInst::PUSHW:
				return "PUSHW";
			case TokenInst::POPW:
				return "POPW";
			case TokenInst::AND:
				return "AND";
			case TokenInst::OR:
				return "OR";
			case TokenInst::XOR:
				return "XOR";
			case TokenInst::ARG:
				return "ARG";
			case TokenInst::PTR:
				return "PTR";
			case TokenInst::STB:
				return "STB";
			case TokenInst::LDB:
				return "LDB";
			case TokenInst::STW:
				return "STW";
			case TokenInst::LDW:
				return "LDW";
			case TokenInst::STR:
				return "STR";
			case TokenInst::RESB:
				return "RESB";
			case TokenInst::PUSHA:
				return "PUSHA";
			case TokenInst::POPA:
				return "POPA";
			case TokenInst::MOVW:
				return "MOVW";
			case TokenInst::ADDW:
				return "ADDW";
			case TokenInst::SUBW:
				return "SUBW";
			case TokenInst::MULW:
				return "MULW";
			case TokenInst::DIVW:
				return "DIVW";
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
			case TokenReg::PC:
				return "%PC";
			default:
				return "%??";
		}
	}

	int Token::getRegToken(char* reg, int line) {
		Util::toCaps(reg);
		
		if (Util::strEquals(reg, "%AX"))
			return TokenReg::AX;
		else if (Util::strEquals(reg, "%BX"))
			return TokenReg::BX;
		else if (Util::strEquals(reg, "%CX"))
			return TokenReg::CX;
		else if (Util::strEquals(reg, "%DX"))
			return TokenReg::DX;
		else if (Util::strEquals(reg, "%XX"))
			return TokenReg::XX;
		else if (Util::strEquals(reg, "%YX"))
			return TokenReg::YX;
		else if (Util::strEquals(reg, "%AL"))
			return TokenReg::AL;
		else if (Util::strEquals(reg, "%BL"))
			return TokenReg::BL;
		else if (Util::strEquals(reg, "%CL"))
			return TokenReg::CL;
		else if (Util::strEquals(reg, "%DL"))
			return TokenReg::DL;
		else if (Util::strEquals(reg, "%XL"))
			return TokenReg::XL;
		else if (Util::strEquals(reg, "%YL"))
			return TokenReg::YL;
		else if (Util::strEquals(reg, "%AH"))
			return TokenReg::AH;
		else if (Util::strEquals(reg, "%BH"))
			return TokenReg::BH;
		else if (Util::strEquals(reg, "%CH"))
			return TokenReg::CH;
		else if (Util::strEquals(reg, "%DH"))
			return TokenReg::DH;
		else if (Util::strEquals(reg, "%XH"))
			return TokenReg::XH;
		else if (Util::strEquals(reg, "%YH"))
			return TokenReg::YH;
		else if (Util::strEquals(reg, "%CF"))
			return TokenReg::CF;
		else if (Util::strEquals(reg, "%CY"))
			return TokenReg::CY;
		else if (Util::strEquals(reg, "%BP"))
			return TokenReg::BP;
		else if (Util::strEquals(reg, "%SP"))
			return TokenReg::SP;
		else if (Util::strEquals(reg, "%RM"))
			return TokenReg::RM;
		else if (Util::strEquals(reg, "%PC"))
			return TokenReg::PC;
		else {
			std::cerr << "Invalid Register (" << line << ") : " << reg << std::endl;
			panic("Aborting");
			return -1; // needed for clean compile
		}
	}

} // namespace VM