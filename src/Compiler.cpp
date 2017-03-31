#include <VM/Compiler.h>

namespace VM {

	Compiler::Compiler(const char* path, TokenList* tokenList) {
		this->tokenList = tokenList;
		this->textBuf = new ByteList(1);
		this->addrList = new IntList(1);
		
		this->addr = 0;
		this->path = path;
	}

	Compiler::~Compiler() {
		delete this->textBuf;
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
					this->addrList->add(this->addr);
					writeByte(0x00);
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
		
		writeOutputFile();
	}

	void Compiler::writeOutputFile() {
		FILE* outputFile = fopen(this->path, "wb");
		ASSERT(outputFile, "Could not open output file");
		
		for (int i = 0; i < this->textBuf->getPointer(); i++) {
			unsigned char b = this->textBuf->get(i);
			fwrite(&b, 1, 1, outputFile);
		}
		
		fclose(outputFile);
	}

	void Compiler::writeByte(unsigned char data) {
		this->textBuf->add(data);
		this->addr++;
	}

} // namespace VM