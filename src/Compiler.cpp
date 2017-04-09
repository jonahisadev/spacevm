#include <VM/Compiler.h>

namespace VM {

	Compiler::Compiler(const char* path, TokenList* tokenList) {
		this->tokenList = tokenList;
		this->textBuf = new List<unsigned char>(1);
		
		this->lblMap = new Map<int, unsigned short>(1);
		this->jmpMap = new Map<int, unsigned short>(1);

		this->addr = 0;
		this->path = path;
	}

	Compiler::~Compiler() {
		delete this->textBuf;
	}
	
	void Compiler::setLabelList(List<char*>* lblList) {
		this->lblList = lblList;
	}
	
	void Compiler::setJumpList(List<char*>* jmpList) {
		this->jmpList = jmpList;
	}

	void Compiler::start() {
		Token* t;

		for (int i = 0; i < tokenList->getPointer(); i++) {
			t = tokenList->get(i);

			// INSTRUCTIONS
			if (t->getType() == TokenType::INST) {
				// MOV
				if (t->getData() == TokenInst::MOV) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::MOV_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::MOV_RR);
				}

				// ADD
				else if (t->getData() == TokenInst::ADD) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::ADD_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::ADD_RR);
				}

				// SUB
				else if (t->getData() == TokenInst::SUB) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::SUB_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::SUB_RR);
				}

				// CALL
				else if (t->getData() == TokenInst::CALL) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::CALL_);
				}

				// RET
				else if (t->getData() == TokenInst::RET) {
					writeByte(ByteInst::RET_);
				}

				// SYSI
				else if (t->getData() == TokenInst::SYSI) {
					writeByte(ByteInst::SYSI_);
				}

				// MUL
				else if (t->getData() == TokenInst::MUL) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::MUL_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::MUL_RR);
				}

				// DIV
				else if (t->getData() == TokenInst::DIV) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::DIV_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::DIV_RR);
				}

				// SXR
				else if (t->getData() == TokenInst::SXR) {
					writeByte(ByteInst::SXR_R);
				}

				// SXL
				else if (t->getData() == TokenInst::SXL) {
					writeByte(ByteInst::SXL_R);
				}

				// INC
				else if (t->getData() == TokenInst::INC) {
					writeByte(ByteInst::INC_R);
				}

				// DEC
				else if (t->getData() == TokenInst::DEC) {
					writeByte(ByteInst::DEC_R);
				}

				// PUSH
				else if (t->getData() == TokenInst::PUSH) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::PUSH_R);
					else if (tokenList->get(i+1)->getType() == TokenType::NUM)
						writeByte(ByteInst::PUSH_N);
				}

				// POP
				else if (t->getData() == TokenInst::POP) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::POP_R);
					else if (tokenList->get(i+1)->getType() == TokenType::INST)
						writeByte(ByteInst::POP_X);
				}
				
				// CMP
				else if (t->getData() == TokenInst::CMP) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::CMP_RR);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::CMP_RN);
				}
				
				// JUMPS
				else if (t->getData() == TokenInst::JMP) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JMP_);
				}
				else if (t->getData() == TokenInst::JNE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JNE_);
				}
				else if (t->getData() == TokenInst::JE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JE_);
				}
				else if (t->getData() == TokenInst::JG) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JG_);
				}
				else if (t->getData() == TokenInst::JL) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JL_);
				}
				else if (t->getData() == TokenInst::JGE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JGE_);
				}
				else if (t->getData() == TokenInst::JLE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JLE_);
				}
				else if (t->getData() == TokenInst::JZ) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JZ_);
				}
				else if (t->getData() == TokenInst::JNZ) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JNZ_);
				}

				// HLT
				else if (t->getData() == TokenInst::HLT) {
					writeByte(ByteInst::HLT_);
				}
			}
			
			// LABELS
			else if (t->getType() == TokenType::LBL) {
				this->lblMap->add(t->getData(), this->addr);
			}
			else if (t->getType() == TokenType::JMP_T) {
				this->jmpMap->add(t->getData(), this->addr);
				// Make room for later
				writeByte(0x00);
				writeByte(0x00);
			}

			// REGISTERS
			else if (t->getType() == TokenType::REG) {
				int b = getByteReg(t->getData());
				if (b != -1) {
					writeByte(b);
				} else {
					std::cerr << "Invalid register: " << b << std::endl;
					panic ("Aborting");
				}
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

		// Fix label jumps
		for (int i = 0; i < jmpMap->getPointer(); i++) {
			int index = jmpMap->getDataA(i);
			char* jmp = Util::strDupFull(jmpList->get(index));
			
			for (int j = 0; j < lblMap->getPointer(); j++) {
				if (Util::strEquals(jmp, lblList->get(j))) {
					unsigned short addr = lblMap->getDataB(j);
					unsigned char* addrw = Util::sToB(addr);
					this->textBuf->set(jmpMap->getDataB(i), addrw[0]);
					this->textBuf->set(jmpMap->getDataB(i)+1, addrw[1]);
					delete[] addrw;
					free(jmp);
					goto endInsideLoop;
				}
			}
			
			std::cerr << "Could not find matching label '" << jmp << "'" << std::endl;
			free(jmp);
			panic("Aborting");
			
			endInsideLoop:
			continue;
		}

		writeByte(ByteInst::HLT_);
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

	unsigned char Compiler::getByteReg(int tokenData) {
		switch (tokenData) {
			case TokenReg::AX:
				return ByteReg::AX_;
			case TokenReg::BX:
				return ByteReg::BX_;
			case TokenReg::CX:
				return ByteReg::CX_;
			case TokenReg::DX:
				return ByteReg::DX_;
			case TokenReg::XX:
				return ByteReg::XX_;
			case TokenReg::YX:
				return ByteReg::YX_;
			case TokenReg::AL:
				return ByteReg::AL_;
			case TokenReg::BL:
				return ByteReg::BL_;
			case TokenReg::CL:
				return ByteReg::CL_;
			case TokenReg::DL:
				return ByteReg::DL_;
			case TokenReg::XL:
				return ByteReg::XL_;
			case TokenReg::YL:
				return ByteReg::YL_;
			case TokenReg::AH:
				return ByteReg::AH_;
			case TokenReg::BH:
				return ByteReg::BH_;
			case TokenReg::CH:
				return ByteReg::CH_;
			case TokenReg::DH:
				return ByteReg::DH_;
			case TokenReg::XH:
				return ByteReg::XH_;
			case TokenReg::YH:
				return ByteReg::YH_;
			case TokenReg::CF:
				return ByteReg::CF_;
			case TokenReg::CY:
				return ByteReg::CY_;
			case TokenReg::BP:
				return ByteReg::BP_;
			case TokenReg::SP:
				return ByteReg::SP_;
			case TokenReg::RM:
				return ByteReg::RM_;
			case TokenReg::PC:
				return ByteReg::PC_;
			default:
				return (unsigned char)-1;
		}
	}

} // namespace VM