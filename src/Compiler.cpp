#include <VM/Compiler.h>

namespace VM {

	Compiler::Compiler(const char* path, TokenList* tokenList) {
		this->tokenList = tokenList;
		this->textBuf = new List<unsigned char>(1);
		
		this->lblMap = new Map<int, unsigned short>(1);
		this->jmpMap = new Map<int, unsigned short>(1);
		this->addrMap = new Map<int, unsigned short>(1);
		this->varMap = new Map<int, unsigned short>(1);

		this->addr = 0;
		this->path = path;
	}

	Compiler::~Compiler() {
		delete this->textBuf;
		delete this->lblMap;
		delete this->jmpMap;
		delete this->addrMap;
		delete this->varMap;
	}
	
	void Compiler::setLabelList(List<char*>* lblList) {
		this->lblList = lblList;
	}
	
	void Compiler::setJumpList(List<char*>* jmpList) {
		this->jmpList = jmpList;
	}
	
	void Compiler::setAddrList(List<char*>* addrList) {
		this->addrList = addrList;
	}
	
	void Compiler::setVarList(List<char*>* varList) {
		this->varList = varList;
	}
	
	void Compiler::setStrList(List<char*>* strList) {
		this->strList = strList;
	}
	
	void Compiler::setBeginLabel(const char* beginLabel) {
		this->beginLabel = beginLabel;
	}

	void Compiler::serror(const char* inst, int line) {
		std::cerr << "Symantics Error (" << line << "): Invalid " << inst << " operand types" << std::endl;
		std::exit(1);
	}

	void Compiler::start() {
		//	
		//	| 2      | 3         | 3          |
		//	| Length | Data Addr | Entry Addr |
		//
		for (int i = 0; i < 8; i++) {
			writeByte(0x00);
		}
		
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
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::ADDR)
						writeByte(ByteInst::MOV_RA);
					else
						serror("MOV", t->getLine());
				}

				// ADD
				else if (t->getData() == TokenInst::ADD) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::ADD_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::ADD_RR);
					else
						serror("ADD", t->getLine());
				}

				// SUB
				else if (t->getData() == TokenInst::SUB) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::SUB_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::SUB_RR);
					else
						serror("SUB", t->getLine());
				}

				// CALL
				else if (t->getData() == TokenInst::CALL) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::CALL_);
					else
						serror("CALL", t->getLine());
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
					else
						serror("MUL", t->getLine());
				}

				// DIV
				else if (t->getData() == TokenInst::DIV) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::DIV_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::DIV_RR);
					else
						serror("DIV", t->getLine());
				}

				// SXR
				else if (t->getData() == TokenInst::SXR) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::SXR_R);
					else
						serror("SXR", t->getLine());
				}

				// SXL
				else if (t->getData() == TokenInst::SXL) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::SXL_R);
					else
						serror("SXL", t->getLine());
				}

				// INC
				else if (t->getData() == TokenInst::INC) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::INC_R);
					else
						serror("INC", t->getLine());
				}

				// DEC
				else if (t->getData() == TokenInst::DEC) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::DEC_R);
					else
						serror("DEC", t->getLine());
				}

				// PUSH
				else if (t->getData() == TokenInst::PUSH) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::PUSH_R);
					else if (tokenList->get(i+1)->getType() == TokenType::NUM)
						writeByte(ByteInst::PUSH_N);
					else
						serror("PUSH", t->getLine());
				}

				// POP
				else if (t->getData() == TokenInst::POP) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::POP_R);
					else if (tokenList->get(i+1)->getType() == TokenType::INST)
						writeByte(ByteInst::POP_X);
					else
						serror("POP", t->getLine());
				}
				
				// CMP
				else if (t->getData() == TokenInst::CMP) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::CMP_RR);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::CMP_RN);
					else
						serror("CMP", t->getLine());
				}
				
				// JUMPS
				else if (t->getData() == TokenInst::JMP) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JMP_);
					else
						serror("JMP", t->getLine());
				}
				else if (t->getData() == TokenInst::JNE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JNE_);
					else
						serror("JNE", t->getLine());
				}
				else if (t->getData() == TokenInst::JE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JE_);
					else
						serror("JE", t->getLine());
				}
				else if (t->getData() == TokenInst::JG) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JG_);
					else
						serror("JG", t->getLine());
				}
				else if (t->getData() == TokenInst::JL) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JL_);
					else
						serror("JL", t->getLine());
				}
				else if (t->getData() == TokenInst::JGE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JGE_);
					else
						serror("JGE", t->getLine());
				}
				else if (t->getData() == TokenInst::JLE) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JLE_);
					else
						serror("JLE", t->getLine());
				}
				else if (t->getData() == TokenInst::JZ) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JZ_);
					else
						serror("JZ", t->getLine());
				}
				else if (t->getData() == TokenInst::JNZ) {
					if (tokenList->get(i+1)->getType() == TokenType::JMP_T)
						writeByte(ByteInst::JNZ_);
					else
						serror("JNZ", t->getLine());
				}
				
				// PUSHW
				else if (t->getData() == TokenInst::PUSHW) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::PUSHW_R);
					else if (tokenList->get(i+1)->getType() == TokenType::NUM)
						writeByte(ByteInst::PUSHW_N);
					else
						serror("PUSHW", t->getLine());
				}
				
				// POPW
				else if (t->getData() == TokenInst::POPW) {
					if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::POPW_R);
					else if (tokenList->get(i+1)->getType() == TokenType::INST)
						writeByte(ByteInst::POPW_X);
					else
						serror("POPW", t->getLine());
				}
				
				// AND
				else if (t->getData() == TokenInst::AND) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::AND_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::AND_RR);
					else
						serror("AND", t->getLine());
				}
				
				// OR
				else if (t->getData() == TokenInst::OR) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::OR_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::OR_RR);
					else
						serror("OR", t->getLine());
				}
				
				// XOR
				else if (t->getData() == TokenInst::XOR) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::XOR_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::XOR_RR);
					else
						serror("XOR", t->getLine());
				}
				
				// PTR
				else if (t->getData() == TokenInst::PTR) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::REG)
						writeByte(ByteInst::PTR_RR);
					else if (tokenList->get(i+1)->getType() == TokenType::REG)
						writeByte(ByteInst::PTR_R);
					else
						serror("PTR", t->getLine());
				}
				
				// STB
				else if (t->getData() == TokenInst::STB) {
					if (tokenList->get(i+1)->getType() == TokenType::VAR &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::STB_);
					else
						serror("STB", t->getLine());
				}
				
				// LDB
				else if (t->getData() == TokenInst::LDB) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::ADDR)
						writeByte(ByteInst::LDB_);
					else
						serror("LDB", t->getLine());
				}
				
				// STW
				else if (t->getData() == TokenInst::STW) {
					if (tokenList->get(i+1)->getType() == TokenType::VAR &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::STW_);
					else
						serror("STW", t->getLine());
				}
				
				// LDW
				else if (t->getData() == TokenInst::LDW) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::ADDR)
						writeByte(ByteInst::LDW_);
					else
						serror("LDW", t->getLine());
				}
				
				// STR
				else if (t->getData() == TokenInst::STR) {
					if (tokenList->get(i+1)->getType() == TokenType::VAR &&
						tokenList->get(i+2)->getType() == TokenType::STRING)
						writeByte(ByteInst::STR_);
					else
						serror("STR", t->getLine());
				}
				
				// PUSHA
				else if (t->getData() == TokenInst::PUSHA) {
					if (tokenList->get(i+1)->getType() == TokenType::INST)
						writeByte(ByteInst::PUSHA_);
					else
						serror("PUSHA", t->getLine());
				}
				
				// POPA
				else if (t->getData() == TokenInst::POPA) {
					if (tokenList->get(i+1)->getType() == TokenType::INST)
						writeByte(ByteInst::POPA_);
					else
						serror("POPA", t->getLine());
				}
				
				// MOVW
				else if (t->getData() == TokenInst::MOVW) {
					if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::NUM)
						writeByte(ByteInst::MOVW_RN);
					else if (tokenList->get(i+1)->getType() == TokenType::REG &&
						tokenList->get(i+2)->getType() == TokenType::ADDR)
						writeByte(ByteInst::MOVW_RA);
					else
						serror("MOVW", t->getLine());
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
			
			// VARIABLES
			else if (t->getType() == TokenType::VAR) {
				this->varMap->add(t->getData(), 0);
			}
			else if (t->getType() == TokenType::ADDR) {
				this->addrMap->add(t->getData(), this->addr);
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
					panic("Aborting");
				}
			}

			// NUMBERS
			else if (t->getType() == TokenType::NUM) {
				Token* storeTk = tokenList->get(i-2);
				if (storeTk->getData() == TokenInst::STB) {
					writeByte(t->getData());
				} else if (storeTk->getData() == TokenInst::STW) {
					unsigned char* num = Util::sToB(t->getData());
					writeByte(num[0]);
					writeByte(num[1]);
				} else {
					if (t->getData() > 255) {
						unsigned char* num = Util::sToB(t->getData());
						writeByte(num[0]);
						writeByte(num[1]);
					} else {
						writeByte(t->getData());
					}
				}
			}
			
			// STRINGS
			else if (t->getType() == TokenType::STRING) {
				char* str = strList->get(t->getData());
				for (int j = 0; j < Util::strLength(str); j++) {
					writeByte((unsigned char)str[j]);
				}
				writeByte(0x00);
			}
			
			// PREPROCESSORS
			else if (t->getType() == TokenType::PPI) {
				if (t->getData() == TokenPPI::DATA) {
					currentDataSection = true;
					unsigned char* addrw = Util::sToB(this->addr);
					this->textBuf->set(2, ByteInst::CALL_);
					this->textBuf->set(3, addrw[0]);
					this->textBuf->set(4, addrw[1]);
					
					// Add data entry to debug symbols
					if (this->symbols) {
						this->lblList->add((char*)"DATA_ENTRY");
						this->lblMap->add(this->lblList->getPointer()-1, this->addr);
					}
				} else if (t->getData() == TokenPPI::END) {
					if (currentDataSection) {
						writeByte(ByteInst::RET_);
					}
				}
			}

			// UNKNOWN
			else {
				panic("Major Compiler Error: Unknown Token Type!\nAborting");
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
		
		// Set variable size offsets
		for (int i = 0; i < varMap->getPointer(); i++) {
			int size = varMap->getDataA(i);
			for (int j = i+1; j < varMap->getPointer(); j++) {
				varMap->setDataB(j, varMap->getDataB(j) + size);
			}
		}
		
		// Fix variable addresses
		for (int i = 0; i < addrMap->getPointer(); i++) {
			int index = addrMap->getDataA(i);
			char* addrName = Util::strDupFull(addrList->get(index));
			
			for (int j = 0; j < varMap->getPointer(); j++) {
				if (Util::strEquals(addrName, varList->get(j))) {
					unsigned char* addrw = Util::sToB(varMap->getDataB(j));
					this->textBuf->set(addrMap->getDataB(i), addrw[0]);
					this->textBuf->set(addrMap->getDataB(i)+1, addrw[1]);
					delete[] addrw;
					free(addrName);
					goto endInsideLoop2;
				}
			}
			
			std::cerr << "Could not find matching variable '" << addrName << "'" << std::endl;
			free(addrName);
			panic("Aborting");
			
			endInsideLoop2:
			continue;
		}
		
		// Write jump to start label
		for (int i = 0; i < lblMap->getPointer(); i++) {
			if (Util::strEquals(lblList->get(i), this->beginLabel)) {
				unsigned short addr = lblMap->getDataB(i);
				unsigned char* addrw = Util::sToB(addr);
				this->textBuf->set(5, ByteInst::JMP_);
				this->textBuf->set(6, addrw[0]);
				this->textBuf->set(7, addrw[1]);
				break;
			}
		}

		writeByte(ByteInst::HLT_);
		
		unsigned short binLen = this->textBuf->getPointer();
		unsigned char* binLenW = Util::sToB(binLen);
		this->textBuf->set(0, binLenW[0]);
		this->textBuf->set(1, binLenW[1]);
		
		writeOutputFile();
		
		// Write debug information if requested
		if (this->symbols) {
			char* nPath = Util::strDupFull((char*)this->path);
			nPath[Util::strLength(path)-1] = 'd';
			FILE* debugFile = fopen(nPath, "w");

			// Write labels
			for (int i = 0; i < this->lblMap->getPointer(); i++) {
				int addr = lblMap->getDataB(i);
				int listPtr = lblMap->getDataA(i);
				char* lblName = lblList->get(listPtr);
				
				fprintf(debugFile, "%d,%s", addr, lblName);
				if (i != this->lblMap->getPointer() - 1)
					fprintf(debugFile, "\n");
			}
			
			fclose(debugFile);
		}
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