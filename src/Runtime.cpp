#include <VM/Runtime.h>

namespace VM {

	Runtime::Runtime(unsigned char* data) {
		this->retCode = 0;
		this->memory = new unsigned char[MEMORY_SIZE];
		
		unsigned char aLen = data[0];
		unsigned char bLen = data[1];
		unsigned short binLen = Util::bToS(aLen, bLen);
		
		for (int i = 0; i < binLen; i++) {
			this->memory[PROG_BASE + i] = data[i];
		}
		
		delete[] data;
	}

	Runtime::~Runtime() {
		delete[] this->memory;
	}

	void Runtime::start() {
		unsigned char opcode = 0;
		bool firstDebug = true;

		Debugger* d = new Debugger(this, &this->memory[PROG_BASE]);

		startWhile:
		if (this->debug) {
			if (firstDebug) {
				d->run(0, false);
				firstDebug = false;
			} else {
				if (d->isBreakpoint(this->pc - PROG_BASE)) {
					d->run(this->pc - PROG_BASE, false);
					goto endDebug;
				}
				if (d->isModeStep()) {
					d->run(this->pc - PROG_BASE, true);
					goto endDebug;
				}
			}
		}

		endDebug:
		while (opcode != ByteInst::HLT_) {
			// startWhile:
			opcode = this->memory[this->pc];

			switch (opcode) {
				
				// NOP
				case ByteInst::NOP: {
					break;
				}

				// MOV
				case ByteInst::MOV_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					Register* regPtr = getRegister(reg);
					regPtr->set(val);
					break;
				}
				case ByteInst::MOV_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					Register* destPtr = getRegister(dest);
					Register* srcPtr = getRegister(src);

					destPtr->set(srcPtr->get());
					break;
				}
				case ByteInst::MOV_RA: {
					unsigned char reg = getNextByte();
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					unsigned short addr = Util::bToS(a, b);
					addr += VAR_OFFSET;
					
					Register* regPtr = getRegister(reg);
					regPtr->set((short)addr);
					break;
				}

				// ADD
				case ByteInst::ADD_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					Register* regPtr = getRegister(reg);
					regPtr->set(regPtr->get() + val);
					break;
				}
				case ByteInst::ADD_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					Register* destPtr = getRegister(dest);
					Register* srcPtr = getRegister(src);

					destPtr->set(destPtr->get() + srcPtr->get());
					break;
				}

				// SUB
				case ByteInst::SUB_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					Register* regPtr = getRegister(reg);
					regPtr->set(regPtr->get() - val);
					break;
				}
				case ByteInst::SUB_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					Register* destPtr = getRegister(dest);
					Register* srcPtr = getRegister(src);

					destPtr->set(destPtr->get() - srcPtr->get());
					break;
				}
				
				// CALL
				case ByteInst::CALL_: {
					// Save return address
					unsigned char* data = Util::sToB(this->pc + 3);
					push(data[1]);
					push(data[0]);
					
					// Jump to address
					jump();
					goto startWhile;
				}
				
				// RET
				case ByteInst::RET_: {
					// Get return address
					unsigned char a = pop();
					unsigned char b = pop();
					
					// Jump to address
					this->pc = Util::bToS(a, b);
					goto startWhile;
				}

				// MUL
				case ByteInst::MUL_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					Register* regPtr = getRegister(reg);
					regPtr->set(regPtr->get() * val);
					break;
				}
				case ByteInst::MUL_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					Register* destPtr = getRegister(dest);
					Register* srcPtr = getRegister(src);

					destPtr->set(destPtr->get() * srcPtr->get());
					break;
				}

				// DIV
				case ByteInst::DIV_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					Register* regPtr = getRegister(reg);
					short save = regPtr->get();

					regPtr->set((short)floor((float)regPtr->get() / (float)val));
					this->rm->set((short)((int)save % (int)val));
					
					break;
				}
				case ByteInst::DIV_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					Register* destPtr = getRegister(dest);
					Register* srcPtr = getRegister(src);
					short save = destPtr->get();

					destPtr->set((short)floor((float)destPtr->get() / (float)srcPtr->get()));
					this->rm->set((short)((int)save % (int)srcPtr->get()));
					
					break;
				}

				// SXL
				case ByteInst::SXL_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					regPtr->set(regPtr->get() << 1);
					break;
				}

				// SXR
				case ByteInst::SXR_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					regPtr->set(regPtr->get() >> 1);
					break;
				}

				// INC
				case ByteInst::INC_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					regPtr->set(regPtr->get() + 1);
					break;
				}

				// DEC
				case ByteInst::DEC_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					regPtr->set(regPtr->get() - 1);
					break;
				}

				// PUSH
				case ByteInst::PUSH_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					unsigned char data = regPtr->get();
					push(data);
					break;
				}
				case ByteInst::PUSH_N: {
					unsigned char num = getNextByte();
					push(num);
					break;
				}

				// POP
				case ByteInst::POP_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					regPtr->set(pop());
					break;
				}
				case ByteInst::POP_X: {
					pop();
					break;
				}

				// CMP
				case ByteInst::CMP_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* aPtr = getRegister(a);
					Register* bPtr = getRegister(b);
					
					cmp(aPtr->get(), bPtr->get());
					break;
				}
				case ByteInst::CMP_RN: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* aPtr = getRegister(a);
					
					cmp(aPtr->get(), b);
					break;
				}
			
				// JUMPS
				case ByteInst::JMP_: {
					jump();
					goto startWhile;
				}
				case ByteInst::JNE_: {
					if (!getFlag(1)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				case ByteInst::JE_: {
					if (getFlag(1)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				case ByteInst::JG_: {
					if (getFlag(3)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				case ByteInst::JL_: {
					if (getFlag(2)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				case ByteInst::JGE_: {
					if (getFlag(1) || getFlag(3)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				case ByteInst::JLE_: {
					if (getFlag(1) || getFlag(2)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				case ByteInst::JZ_: {
					if (getFlag(4)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				case ByteInst::JNZ_: {
					if (!getFlag(4)) {
						jump();
						goto startWhile;
					}
					this->pc += 2;
					break;
				}
				
				// PUSHW
				case ByteInst::PUSHW_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					short data = regPtr->get();
					pushw(data);
					break;
				}
				case ByteInst::PUSHW_N: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					short num = (short)Util::bToS(a, b);
					
					pushw(num);
					break;
				}

				// POPW
				case ByteInst::POPW_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);

					regPtr->set(popw());
					break;
				}
				case ByteInst::POPW_X: {
					popw();
					break;
				}
				
				// AND
				case ByteInst::AND_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();
					
					Register* regPtr = getRegister(reg);
					regPtr->set(regPtr->get() & val);
					break;
				}
				case ByteInst::AND_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* aPtr = getRegister(a);
					Register* bPtr = getRegister(b);
					
					aPtr->set(aPtr->get() & bPtr->get());
					break;
				}
				
				// OR
				case ByteInst::OR_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();
					
					Register* regPtr = getRegister(reg);
					regPtr->set(regPtr->get() | val);
					break;
				}
				case ByteInst::OR_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* aPtr = getRegister(a);
					Register* bPtr = getRegister(b);
					
					aPtr->set(aPtr->get() | bPtr->get());
					break;
				}
				
				// XOR
				case ByteInst::XOR_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();
					
					Register* regPtr = getRegister(reg);
					regPtr->set(regPtr->get() ^ val);
					break;
				}
				case ByteInst::XOR_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* aPtr = getRegister(a);
					Register* bPtr = getRegister(b);
					
					aPtr->set(aPtr->get() ^ bPtr->get());
					break;
				}
				
				// PTR
				case ByteInst::PTR_R: {
					unsigned char reg = getNextByte();
					Register* regPtr = getRegister(reg);
					
					unsigned char data = memory[regPtr->get()];
					regPtr->set(data);
					break;
				}
				case ByteInst::PTR_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* aPtr = getRegister(a);
					Register* bPtr = getRegister(b);
					
					unsigned char data = memory[bPtr->get()];
					aPtr->set(data);
					
					break;
				}
				
				// STB
				case ByteInst::STB_: {
					unsigned char data = getNextByte();
					memory[VAR_OFFSET + var_ptr] = data;
					var_ptr += 1;
					break;
				}
				
				// LDB
				case ByteInst::LDB_: {
					unsigned char reg = getNextByte();
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* regPtr = getRegister(reg);
					unsigned short addr = Util::bToS(a, b);
					
					regPtr->set(memory[VAR_OFFSET + addr]);
					break;
				}
				
				// STW
				case ByteInst::STW_: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					memory[VAR_OFFSET + var_ptr++] = a;
					memory[VAR_OFFSET + var_ptr++] = b;
					
					break;
				}
				
				// LDW
				case ByteInst::LDW_: {
					unsigned reg = getNextByte();
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					Register* regPtr = getRegister(reg);
					unsigned short addr = Util::bToS(a, b);
					
					short data = Util::bToS(memory[VAR_OFFSET + addr],
						memory[VAR_OFFSET + addr + 1]);
						
					regPtr->set(data);
					break;
				}
				
				// STR
				case ByteInst::STR_: {
					char data = getNextByte();
					while (data != 0) {
						memory[VAR_OFFSET + var_ptr++] = data;
						data = getNextByte();
					}
					memory[VAR_OFFSET + var_ptr++] = 0;
					break;
				}
				
				// PUSHA
				case ByteInst::PUSHA_: {
					pushw(this->ax->get());
					pushw(this->bx->get());
					pushw(this->cx->get());
					pushw(this->dx->get());
					pushw(this->xx->get());
					pushw(this->yx->get());
					break;
				}
				
				// POPA
				case ByteInst::POPA_: {
					this->yx->set(popw());
					this->xx->set(popw());
					this->dx->set(popw());
					this->cx->set(popw());
					this->bx->set(popw());
					this->ax->set(popw());
					break;
				}
				
				// MOVW
				case MOVW_RN: {
					unsigned char reg = getNextByte();
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					short val = (short)Util::bToS(a, b);
					Register* regPtr = getRegister(reg);
					
					regPtr->set(val);
					break;
				}
				case MOVW_RA: {
					unsigned char reg = getNextByte();
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					unsigned short addr = Util::bToS(a, b);
					Register* regPtr = getRegister(reg);
					
					regPtr->set((short)addr);
					break;
				}

				// SYSI
				case ByteInst::SYSI_: {
					if (this->debug) {
						//std::cout << "INST: " << ByteInst::SYSI_ << std::endl;
					}
					
					if (this->ax->get() == 0x01) {
						sys_exit(this->bx->get());
						goto endLoop;
					}
					else if (this->ax->get() == 0x02) {
						sys_print_b(this->bx->get());
						break;
					}
					else if (this->ax->get() == 0x03) {
						sys_print_c((char)this->bx->get());
						break;
					}
					else if (this->ax->get() == 0x04) {
						sys_print_w(this->bx->get());
						break;
					}
				}
				
			}
			
			this->pc++;
			
			if (debug)
				goto startWhile;
		}
		
		endLoop:
		return;
	}

	unsigned char Runtime::getNextByte() {
		return this->memory[++this->pc];
	}

	void Runtime::push(unsigned char data) {
		if (this->sp < STACK_MAX)
			this->memory[++this->sp] = data;
	}

	unsigned char Runtime::pop() {
		return this->memory[this->sp--];
	}
	
	void Runtime::pushw(short data) {
		unsigned char* dataw = Util::sToB(data);
		push(dataw[1]);
		push(dataw[0]);
	}
	
	short Runtime::popw() {
		unsigned char a = this->memory[this->sp--];
		unsigned char b = this->memory[this->sp--];
		short data = (short)Util::bToS(a, b);
		return data;
	}
	
	void Runtime::cmp(short a, short b) {
		if (a == b)
			this->cf |= 0b0001;
		else
			this->cf &= 0b1110;
		
		if (a < b)
			this->cf |= 0b0010;
		else
			this->cf &= 0b1101;
			
		if (a > b)
			this->cf |= 0b0100;
		else	
			this->cf &= 0b1011;
		
		if ((a - b) == 0)
			this->cf |= 0b1000;
		else
			this->cf &= 0b0111;
	}
	
	void Runtime::jump() {
		unsigned char addrA = getNextByte();
		unsigned char addrB = getNextByte();
		this->pc = Util::bToS(addrA, addrB) + PROG_BASE;
	}
	
	bool Runtime::getFlag(int ptr) {
		return (bool)((this->cf >> (ptr-1)) & 0b0001);
	}

	// SYSTEM INTERRUPTS

	void Runtime::sys_exit(int code) {
		this->retCode = code;
	}

	void Runtime::sys_print_b(unsigned char b) {
		std::cout << (int)b;
	}

	void Runtime::sys_print_c(char c) {
		std::cout << c;
	}
	
	void Runtime::sys_print_w(short w) {
		std::cout << w;
	}

	Register* Runtime::getRegister(unsigned char reg) {
		// AX
		if (reg == ByteReg::AX_) {
			this->ax->setReferenceType(RegRef::R_FULL);
			return this->ax;
		} else if (reg == ByteReg::AL_) {
			this->ax->setReferenceType(RegRef::R_LOW);
			return this->ax;
		}
		else if (reg == ByteReg::AH_) {
			this->ax->setReferenceType(RegRef::R_HIGH);
			return this->ax;
		}
		
		// BX
		if (reg == ByteReg::BX_) {
			this->bx->setReferenceType(RegRef::R_FULL);
			return this->bx;
		} else if (reg == ByteReg::BL_) {
			this->bx->setReferenceType(RegRef::R_LOW);
			return this->bx;
		}
		else if (reg == ByteReg::BH_) {
			this->bx->setReferenceType(RegRef::R_HIGH);
			return this->bx;
		}
		
		// CX
		if (reg == ByteReg::CX_) {
			this->cx->setReferenceType(RegRef::R_FULL);
			return this->cx;
		} else if (reg == ByteReg::CL_) {
			this->cx->setReferenceType(RegRef::R_LOW);
			return this->cx;
		}
		else if (reg == ByteReg::CH_) {
			this->cx->setReferenceType(RegRef::R_HIGH);
			return this->cx;
		}
		
		// DX
		if (reg == ByteReg::DX_) {
			this->dx->setReferenceType(RegRef::R_FULL);
			return this->dx;
		} else if (reg == ByteReg::DL_) {
			this->dx->setReferenceType(RegRef::R_LOW);
			return this->dx;
		}
		else if (reg == ByteReg::DH_) {
			this->dx->setReferenceType(RegRef::R_HIGH);
			return this->dx;
		}
		
		// XX
		if (reg == ByteReg::XX_) {
			this->xx->setReferenceType(RegRef::R_FULL);
			return this->xx;
		} else if (reg == ByteReg::XL_) {
			this->xx->setReferenceType(RegRef::R_LOW);
			return this->xx;
		}
		else if (reg == ByteReg::XH_) {
			this->xx->setReferenceType(RegRef::R_HIGH);
			return this->xx;
		}
		
		// YX
		if (reg == ByteReg::YX_) {
			this->yx->setReferenceType(RegRef::R_FULL);
			return this->yx;
		} else if (reg == ByteReg::YL_) {
			this->yx->setReferenceType(RegRef::R_LOW);
			return this->yx;
		}
		else if (reg == ByteReg::YH_) {
			this->yx->setReferenceType(RegRef::R_HIGH);
			return this->yx;
		}
		
		else if (reg == ByteReg::RM_) {
			return this->rm;
		}

		else {
			std::cerr << "Unknown Register: " << (int)reg << std::endl;
			panic("Aborting");
			return nullptr;
		}
	}
	
	// DEBUG FUNCTIONS
	
	void Runtime::printRegisters() {
		std::cout << "\t\tAX: " << ax->get() << std::endl;
		std::cout << "\t\tBX: " << bx->get() << std::endl;
		std::cout << "\t\tCX: " << cx->get() << std::endl;
		std::cout << "\t\tDX: " << dx->get() << std::endl;
		std::cout << "\t\tXX: " << xx->get() << std::endl;
		std::cout << "\t\tYX: " << yx->get() << std::endl;
		std::cout << "\t\tRM: " << rm->get() << std::endl;
	}
	
	void Runtime::printStack(unsigned short addr) {
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 16; x++) {
				std::cout << this->memory[addr + (y * 16 + x)];
				if (y != 15 && x != 15) {
					std::cout << ", ";
				}
			}
			std::cout << std::endl;
		}
	}

} // namespace VM