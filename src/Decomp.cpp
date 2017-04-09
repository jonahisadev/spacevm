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
				case SUB_RN: {
					std::printf("SUB \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case SYSI_: {
					std::printf("SYSI");
					addr++;
					break;
				}
				case MUL_RN: {
					std::printf("MUL \t%s %d", 
					Token::getRegister(data[addr+1]), 
					data[addr+2]);
					addr += 3;
					break;
				}
				case INC_R: {
					std::printf("INC \t%s", 
					Token::getRegister(data[addr+1]));
					addr += 2;
					break;
				}
				case CMP_RR: {
					std::printf("CMP \t%s %s", 
					Token::getRegister(data[addr+1]), 
					Token::getRegister(data[addr+2]));
					addr += 3;
					break;
				}
				case JMP_: {
					std::printf("JMP \t0x%02d%02d",
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
				case HLT_: {
					running = false;
					break;
				}
				default: {
					addr++;
				}
			}
			
			std::printf("\n");
		}
	}
	
} // namespace VM