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
			startWhile:
			opcode = this->data[this->pc];

			switch (opcode) {

				// MOV
				case ByteInst::MOV_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					short* regPtr = getRegister(reg);
					*regPtr = val;
					break;
				}
				case ByteInst::MOV_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					short* destPtr = getRegister(dest);
					short* srcPtr = getRegister(src);

					*destPtr = *srcPtr;
					break;
				}

				// ADD
				case ByteInst::ADD_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					short* regPtr = getRegister(reg);
					*regPtr += val;
					break;
				}
				case ByteInst::ADD_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					short* destPtr = getRegister(dest);
					short* srcPtr = getRegister(src);

					*destPtr += *srcPtr;
					break;
				}

				// SUB
				case ByteInst::SUB_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					short* regPtr = getRegister(reg);
					*regPtr -= val;
					break;
				}
				case ByteInst::SUB_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					short* destPtr = getRegister(dest);
					short* srcPtr = getRegister(src);

					*destPtr -= *srcPtr;
					break;
				}
				
				// CALL
				case ByteInst::CALL_: {
					// Save return address
					unsigned char* data = Util::sToB(this->pc + 3);
					push(data[1]);
					push(data[0]);
					
					// Jump to address
					this->pc = Util::bToS(getNextByte(), getNextByte());
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

					short* regPtr = getRegister(reg);
					*regPtr *= val;
					break;
				}
				case ByteInst::MUL_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					short* destPtr = getRegister(dest);
					short* srcPtr = getRegister(src);

					*destPtr *= *srcPtr;
					break;
				}

				// DIV
				case ByteInst::DIV_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();

					short* regPtr = getRegister(reg);
					short save = *regPtr;

					*regPtr = (short)floor((float)*regPtr / (float)val);
					this->rm = (short)((int)save % (int)val);
					
					break;
				}
				case ByteInst::DIV_RR: {
					unsigned char dest = getNextByte();
					unsigned char src = getNextByte();

					short* destPtr = getRegister(dest);
					short* srcPtr = getRegister(src);
					short save = *destPtr;

					*destPtr = (short)floor((float)*destPtr / (float)*srcPtr);
					this->rm = (short)((int)save % (int)*srcPtr);
					
					break;
				}

				// SXL
				case ByteInst::SXL_R: {
					unsigned char reg = getNextByte();
					short* regPtr = getRegister(reg);

					*regPtr = *regPtr << 1;
					break;
				}

				// SXR
				case ByteInst::SXR_R: {
					unsigned char reg = getNextByte();
					short* regPtr = getRegister(reg);

					*regPtr = *regPtr >> 1;
					break;
				}

				// INC
				case ByteInst::INC_R: {
					unsigned char reg = getNextByte();
					short* regPtr = getRegister(reg);

					*regPtr += 1;
					break;
				}

				// DEC
				case ByteInst::DEC_R: {
					unsigned char reg = getNextByte();
					short* regPtr = getRegister(reg);

					*regPtr -= 1;
					break;
				}

				// PUSH
				case ByteInst::PUSH_R: {
					unsigned char reg = getNextByte();
					short* regPtr = getRegister(reg);

					unsigned char data = *regPtr;
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
					short* regPtr = getRegister(reg);

					*regPtr = pop();
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
					
					short* aPtr = getRegister(a);
					short* bPtr = getRegister(b);
					
					cmp(*aPtr, *bPtr);
					break;
				}
				case ByteInst::CMP_RN: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					short* aPtr = getRegister(a);
					
					cmp(*aPtr, b);
					break;
				}
			
				// JUMPS
				case ByteInst::JMP_: {
					this->pc = Util::bToS(getNextByte(), getNextByte());
					goto startWhile;
				}
				case ByteInst::JNE_: {
					if (!getFlag(1)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				case ByteInst::JE_: {
					if (getFlag(1)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				case ByteInst::JG_: {
					if (getFlag(3)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				case ByteInst::JL_: {
					if (getFlag(2)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				case ByteInst::JGE_: {
					if (getFlag(1) || getFlag(3)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				case ByteInst::JLE_: {
					if (getFlag(1) || getFlag(2)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				case ByteInst::JZ_: {
					if (getFlag(4)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				case ByteInst::JNZ_: {
					if (!getFlag(4)) {
						this->pc = Util::bToS(getNextByte(), getNextByte());
						goto startWhile;
					}
				}
				
				// AND
				case ByteInst::AND_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();
					
					short* regPtr = getRegister(reg);
					*regPtr &= val;
					break;
				}
				case ByteInst::AND_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					short* aPtr = getRegister(a);
					short* bPtr = getRegister(b);
					
					*aPtr &= *bPtr;
					break;
				}
				
				// OR
				case ByteInst::OR_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();
					
					short* regPtr = getRegister(reg);
					*regPtr |= val;
					break;
				}
				case ByteInst::OR_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					short* aPtr = getRegister(a);
					short* bPtr = getRegister(b);
					
					*aPtr |= *bPtr;
					break;
				}
				
				// XOR
				case ByteInst::XOR_RN: {
					unsigned char reg = getNextByte();
					unsigned char val = getNextByte();
					
					short* regPtr = getRegister(reg);
					*regPtr ^= val;
					break;
				}
				case ByteInst::XOR_RR: {
					unsigned char a = getNextByte();
					unsigned char b = getNextByte();
					
					short* aPtr = getRegister(a);
					short* bPtr = getRegister(b);
					
					*aPtr ^= *bPtr;
					break;
				}

				// SYSI
				case ByteInst::SYSI_: {
					if (this->ax == 0x01) {
						sys_exit(this->bx);
						goto endLoop;
					}
					else if (this->ax == 0x02) {
						sys_print_b(this->bx);
					}
					else if (this->ax == 0x03) {
						sys_print_c((char)this->bx);
					}
				}
				
			}
			
			this->pc++;
		}
		
		endLoop:
		return;
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