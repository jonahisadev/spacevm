#include <VM/Compiler.h>

namespace VM {

	Compiler::Compiler(const char* path, TokenList* tokenList) {
		this->tokenList = tokenList;
		this->obj_file = fopen(path, "wb");
	}

	Compiler::~Compiler() {
		// Nothing
	}

	void Compiler::start() {
		Token* t;

		for (int i = 0; i < tokenList->getPointer(); i++) {
			t = tokenList->get(i);

			// INSTRUCTIONS
			if (t->getType() == TokenType::INST) {
				if (t->getData() == TokenInst::MOV) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::MOV_RN);
				}
			}

			// REGISTERS
			if (t->getType() == TokenType::REG) {
				if (t->getData() == TokenReg::AX)
					writeByte(ByteReg::AX_);
				else if (t->getData() == TokenReg::BX)
					writeByte(ByteReg::BX_);
			}

			// NUMBERS
			if (t->getType() == TokenType::NUM) {
				writeByte((unsigned char)t->getData());
			}

		}
	}

	void Compiler::writeByte(unsigned char data) {
		fwrite(&data, 1, 1, this->obj_file);
	}

}