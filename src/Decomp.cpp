#include <VM/Decomp.h>

namespace VM {
	
	Decomp::Decomp(unsigned char* data) {
		this->data = data;
	}
	
	Decomp::~Decomp() {
		free(this->data);
	}
	
	void Decomp::start() {
		unsigned short addr = 0;
		bool running = true;
		
		while (running) {
			unsigned char opcode = data[addr];
			if (opcode == HLT_)
				break;
				
			std::printf("%04d: ", addr);
			
			switch(opcode) {
				// NOP
				case NOP: {
					std::printf("NOP");
					addr++;
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
					std::printf("CALL \t0x%02d%02d",
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
					std::printf("JMP \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JNE_: {
					std::printf("JNE \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JE_: {
					std::printf("JE \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JG_: {
					std::printf("JG \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JL_: {
					std::printf("JL \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JGE_: {
					std::printf("JGE \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JLE_: {
					std::printf("JLE \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JZ_: {
					std::printf("JZ \t0x%02d%02d",
					data[addr+1], data[addr+2]);
					addr += 3;
					break;
				}
				case JNZ_: {
					std::printf("JNZ \t0x%02d%02d",
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