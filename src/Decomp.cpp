#include <VM/Decomp.h>

namespace VM {
	
	Decomp::Decomp(unsigned char* data) {
		this->data = data;
	}
	
	Decomp::~Decomp() {
		free(this->data);
	}
	
	void Decomp::start() {
		unsigned char a = data[0];
		unsigned char b = data[1];
		unsigned short binLen = Util::bToS(a, b);
		
		std::printf("LEN:  %d\n", binLen);
		
		unsigned short addr = 2;
		bool running = true;
		
		while (running) {
			unsigned char opcode = data[addr];
			if (opcode == HLT_)
				break;
				
			std::printf("%04X: ", addr);
			
			switch(opcode) {
				// NOP
				case NOP: {
					std::printf("NOP");
					addr++;
					break;
				}
				
				// MOV
				case MOV_RN: {
					std::printf("MOV \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case MOV_RR: {
					std::printf("MOV \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				case MOV_RA: {
					std::printf("MOV \t%s &%02X%02X", 
					Token::getRegister(data[addr+1]), 
					data[addr+2], data[addr+3]);
					addr += 4;
					break;
				}
				
				// ADD
				case ADD_RN: {
					std::printf("ADD \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case ADD_RR: {
					std::printf("ADD \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// SUB
				case SUB_RN: {
					std::printf("SUB \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case SUB_RR: {
					std::printf("SUB \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// CALL
				case CALL_: {
					std::printf("CALL \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				
				// RET
				case RET_: {
					std::printf("RET");
					addr++;
					break;
				}
				
				// SYSI
				case SYSI_: {
					std::printf("SYSI");
					addr++;
					break;
				}
				
				// MUL
				case MUL_RN: {
					std::printf("MUL \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case MUL_RR: {
					std::printf("MUL \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// MUL
				case DIV_RN: {
					std::printf("DIV \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case DIV_RR: {
					std::printf("DIV \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// SXR
				case SXR_R: {
					std::printf("SXR \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				
				// SXL
				case SXL_R: {
					std::printf("SXL \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				
				// INC
				case INC_R: {
					std::printf("INC \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				
				// DEC
				case DEC_R: {
					std::printf("DEC \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				
				// PUSH
				case PUSH_R: {
					std::printf("PUSH \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				case PUSH_N: {
					std::printf("PUSH \t%d", 
					data[addr+1]);
					addr += 2;
					break;
				}
				
				// POP
				case POP_R: {
					std::printf("POP \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				case POP_X: {
					std::printf("POP");
					addr++;
					break;
				}
				
				// CMP
				case CMP_RR: {
					std::printf("CMP \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				case CMP_RN: {
					std::printf("CMP \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				
				// JUMPS
				case JMP_: {
					std::printf("JMP \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JNE_: {
					std::printf("JNE \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JE_: {
					std::printf("JE \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JG_: {
					std::printf("JG \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JL_: {
					std::printf("JL \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JGE_: {
					std::printf("JGE \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JLE_: {
					std::printf("JLE \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JZ_: {
					std::printf("JZ \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JNZ_: {
					std::printf("JNZ \t&%02X%02X",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				
				// AND
				case AND_RN: {
					std::printf("AND \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case AND_RR: {
					std::printf("AND \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// OR
				case OR_RN: {
					std::printf("OR \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case OR_RR: {
					std::printf("OR \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// XOR
				case XOR_RN: {
					std::printf("XOR \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case XOR_RR: {
					std::printf("XOR \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// PTR
				case PTR_R: {
					std::printf("PTR \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				case PTR_RR: {
					std::printf("PTR \t%s %s",
					Token::getRegister(data[addr+1]),
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				
				// STB
				case STB_: {
					std::printf("STB \t%d", 
					data[addr+1]);
					addr += 2;
					break;
				}
				
				// LDB
				case LDB_: {
					std::printf("LDB \t%s &%02X%02X",
					Token::getRegister(data[addr+1]),
					data[addr+2], data[addr+3]);
					addr += 4;
					break;
				}
				
				// STW
				case STW_: {
					std::printf("STW \t%d",
					Util::bToS(data[addr+1], data[addr+2]));
					addr += 3;
					break;
				}
				
				// LDW
				case LDW_: {
					std::printf("LDW \t%s &%02X%02X",
					Token::getRegister(data[addr + 1]),
					data[addr+2], data[addr+3]);
					addr += 4;
					break;
				}
				
				// STR
				case STR_: {
					std::printf("%s\t\"", "STR");
					unsigned char c = data[++addr];
					while (c != 0) {
						std::printf("%c", (char)c);
						c = data[++addr];
					}
					std::printf("\"");
					addr++;
					break;
				}
				
				// DEFAULT
				default: {
					std::printf("???");
					addr++;
				}
			}
			
			std::printf("\n");
		}
	}
	
} // namespace VM