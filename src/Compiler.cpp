#include <VM/Compiler.h>

namespace VM {

	Compiler::Compiler(const char* path, TokenList* tokenList) {
		this->tokenList = tokenList;
		this->obj_file = fopen(path, "wb");
	}

	Compiler::~Compiler() {
		fclose(this->obj_file);
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
				else if (t->getData() == TokenInst::ADD) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::ADD_RN);
				}
				else if (t->getData() == TokenInst::SUB) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::SUB_RN);
				}
				else if (t->getData() == TokenInst::CALL) {
					writeByte(ByteInst::CALL_);
					writeByte(0x00);
					// TODO: implement address-y things
				}
				else if (t->getData() == TokenInst::RET) {
					writeByte(ByteInst::RET_);
				}
				else if (t->getData() == TokenInst::SYSI) {
					writeByte(ByteInst::SYSI_);
				}
			}

			// REGISTERS
			else if (t->getType() == TokenType::REG) {
				if (t->getData() == TokenReg::AX)
					writeByte(ByteReg::AX_);
				else if (t->getData() == TokenReg::BX)
					writeByte(ByteReg::BX_);
			}

			// NUMBERS
			else if (t->getType() == TokenType::NUM) {
				writeByte(t->getData());
			}
			
			// UNKNOWN
			else {
				std::cerr << "Major Compiler Error: Unknown Token Type!" << std::endl;
				panic("Aborting");
			}
		}
	}

	void Compiler::writeByte(unsigned char data) {
		fwrite(&data, 1, 1, this->obj_file);
	}

}