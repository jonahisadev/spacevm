#include <VM/Runtime.h>

namespace VM {

	Runtime::Runtime(unsigned char* data) {
		this->retCode = 0;
		this->data = data;
		this->memory = new unsigned char[MEMORY_SIZE];
	}

	Runtime::~Runtime() {
		delete[] this->data;
		delete[] this->memory;
	}

	void Runtime::start() {
		unsigned char opcode = 0;

		while (opcode != ByteInst::HLT_) {
			opcode = this->data[this->pc];

			// MOV
			if (opcode == ByteInst::MOV_RN) {
				unsigned char reg = getNextByte();
				unsigned char val = getNextByte();

				short* regPtr = getRegister(reg);
				*regPtr = val;
			}
			else if (opcode == ByteInst::MOV_RR) {
				unsigned char dest = getNextByte();
				unsigned char src = getNextByte();

				short* destPtr = getRegister(dest);
				short* srcPtr = getRegister(src);

				*destPtr = *srcPtr;
			}

			// ADD
			else if (opcode == ByteInst::ADD_RN) {
				unsigned char reg = getNextByte();
				unsigned char val = getNextByte();

				short* regPtr = getRegister(reg);
				*regPtr += val;
			}
			else if (opcode == ByteInst::ADD_RR) {
				unsigned char dest = getNextByte();
				unsigned char src = getNextByte();

				short* destPtr = getRegister(dest);
				short* srcPtr = getRegister(src);

				*destPtr += *srcPtr;
			}

			// SUB
			else if (opcode == ByteInst::SUB_RN) {
				unsigned char reg = getNextByte();
				unsigned char val = getNextByte();

				short* regPtr = getRegister(reg);
				*regPtr -= val;
			}
			else if (opcode == ByteInst::SUB_RR) {
				unsigned char dest = getNextByte();
				unsigned char src = getNextByte();

				short* destPtr = getRegister(dest);
				short* srcPtr = getRegister(src);

				*destPtr -= *srcPtr;
			}
			
			// CALL
			else if (opcode == ByteInst::CALL_) {
				// Save return address
				unsigned char* data = Util::sToB(this->pc + 3);
				push(data[1]);
				push(data[0]);
				
				// Jump to address
				this->pc = Util::bToS(getNextByte(), getNextByte());
				continue;
			}
			
			// RET
			else if (opcode == ByteInst::RET_) {
				// Get return address
				unsigned char a = pop();
				unsigned char b = pop();
				
				// Jump to address
				this->pc = Util::bToS(a, b);
				continue;
			}

			// MUL
			else if (opcode == ByteInst::MUL_RN) {
				unsigned char reg = getNextByte();
				unsigned char val = getNextByte();

				short* regPtr = getRegister(reg);
				*regPtr *= val;
			}
			else if (opcode == ByteInst::MUL_RR) {
				unsigned char dest = getNextByte();
				unsigned char src = getNextByte();

				short* destPtr = getRegister(dest);
				short* srcPtr = getRegister(src);

				*destPtr *= *srcPtr;
			}

			// DIV
			else if (opcode == ByteInst::DIV_RN) {
				unsigned char reg = getNextByte();
				unsigned char val = getNextByte();

				short* regPtr = getRegister(reg);
				short save = *regPtr;

				*regPtr = (short)floor((float)*regPtr / (float)val);
				this->rm = (short)((int)save % (int)val);
			}
			else if (opcode == ByteInst::DIV_RR) {
				unsigned char dest = getNextByte();
				unsigned char src = getNextByte();

				short* destPtr = getRegister(dest);
				short* srcPtr = getRegister(src);
				short save = *destPtr;

				*destPtr = (short)floor((float)*destPtr / (float)*srcPtr);
				this->rm = (short)((int)save % (int)*srcPtr);
			}

			// SXL
			else if (opcode == ByteInst::SXL_R) {
				unsigned char reg = getNextByte();
				short* regPtr = getRegister(reg);

				*regPtr = *regPtr << 1;
			}

			// SXR
			else if (opcode == ByteInst::SXR_R) {
				unsigned char reg = getNextByte();
				short* regPtr = getRegister(reg);

				*regPtr = *regPtr >> 1;
			}

			// INC
			else if (opcode == ByteInst::INC_R) {
				unsigned char reg = getNextByte();
				short* regPtr = getRegister(reg);

				*regPtr += 1;
			}

			// DEC
			else if (opcode == ByteInst::DEC_R) {
				unsigned char reg = getNextByte();
				short* regPtr = getRegister(reg);

				*regPtr -= 1;
			}

			// PUSH
			else if (opcode == ByteInst::PUSH_R) {
				unsigned char reg = getNextByte();
				short* regPtr = getRegister(reg);

				unsigned char data = *regPtr;
				push(data);
			}
			else if (opcode == ByteInst::PUSH_N) {
				unsigned char num = getNextByte();
				push(num);
			}

			// POP
			else if (opcode == ByteInst::POP_R) {
				unsigned char reg = getNextByte();
				short* regPtr = getRegister(reg);

				*regPtr = pop();
			}
			else if (opcode == ByteInst::POP_X) {
				pop();
			}

			// CMP
			else if (opcode == ByteInst::CMP_RR) {
				unsigned char a = getNextByte();
				unsigned char b = getNextByte();
				
				short* aPtr = getRegister(a);
				short* bPtr = getRegister(b);
				
				cmp(*aPtr, *bPtr);
			}
			else if (opcode == ByteInst::CMP_RN) {
				unsigned char a = getNextByte();
				unsigned char b = getNextByte();
				
				short* aPtr = getRegister(a);
				
				cmp(*aPtr, b);
			}
			
			// JUMPS
			else if (opcode == ByteInst::JMP_) {
				this->pc = Util::bToS(getNextByte(), getNextByte());
				continue;
			}
			else if (opcode == ByteInst::JNE_) {
				if (!getFlag(1)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}
			else if (opcode == ByteInst::JE_) {
				if (getFlag(1)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}
			else if (opcode == ByteInst::JG_) {
				if (getFlag(3)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}
			else if (opcode == ByteInst::JL_) {
				if (getFlag(2)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}
			else if (opcode == ByteInst::JGE_) {
				if (getFlag(1) || getFlag(3)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}
			else if (opcode == ByteInst::JLE_) {
				if (getFlag(1) || getFlag(2)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}
			else if (opcode == ByteInst::JZ_) {
				if (getFlag(4)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}
			else if (opcode == ByteInst::JNZ_) {
				if (!getFlag(4)) {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					continue;
				}
			}

			// SYSI
			else if (opcode == ByteInst::SYSI_) {
				if (this->ax == 0x01) {
					sys_exit(this->bx);
					break;
				}
				else if (this->ax == 0x02) {
					sys_print_b(this->bx);
				}
				else if (this->ax == 0x03) {
					sys_print_c((char)this->bx);
				}
			}
			
			this->pc++;
		}
	}

	unsigned char Runtime::getNextByte() {
		return this->data[++this->pc];
	}

	void Runtime::push(unsigned char data) {
		if (this->sp < STACK_MAX)
			this->memory[++this->sp] = data;
	}

	short Runtime::pop() {
		return (short)this->memory[this->sp--];
	}
	
	void Runtime::cmp(short a, short b) {
		if (a == b)
			this->cf = (this->cf | 0b0001);
		else
			this->cf = (this->cf & 0b1110);
		
		if (a < b)
			this->cf = (this->cf | 0b0010);
		else
			this->cf = (this->cf & 0b1101);
			
		if (a > b)
			this->cf = (this->cf | 0b0100);
		else	
			this->cf = (this->cf & 0b1011);
		
		if ((a - b) == 0)
			this->cf = (this->cf | 0b1000);
		else
			this->cf = (this->cf & 0b0111);
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

	short* Runtime::getRegister(unsigned char reg) {
		if (reg == ByteReg::AX_) {
			return &this->ax;
		}
		else if (reg == ByteReg::BX_) {
			return &this->bx;
		}
		else if (reg == ByteReg::CX_) {
			return &this->cx;
		}
		else if (reg == ByteReg::DX_) {
			return &this->dx;
		}
		else if (reg == ByteReg::XX_) {
			return &this->xx;
		}
		else if (reg == ByteReg::YX_) {
			return &this->yx;
		}
		else if (reg == ByteReg::RM_) {
			return &this->rm;
		}

		else {
			return nullptr;
		}
	}

} // namespace VM