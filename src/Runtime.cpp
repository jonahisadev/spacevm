#include <VM/Runtime.h>

namespace VM {

	Runtime::Runtime(unsigned char* data) {
		this->retCode = 0;
		this->data = data;
	}

	Runtime::~Runtime() {
		delete[] this->data;
	}

	void Runtime::start() {
		unsigned char opcode = 0;

		while (opcode != ByteInst::HLT_) {
			opcode = this->data[++this->pc];

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
			
			// SUB
			else if (opcode == ByteInst::SUB_RN) {
				unsigned char reg = getNextByte();
				unsigned char val = getNextByte();
				
				short* regPtr = getRegister(reg);
				*regPtr -= val;
			}
			
			// MUL
			else if (opcode == ByteInst::MUL_RN) {
				unsigned char reg = getNextByte();
				unsigned char val = getNextByte();
				
				short* regPtr = getRegister(reg);
				*regPtr *= val;
			}
			
			// SYSI
			else if (opcode == ByteInst::SYSI_) {
				if (this->ax == 0x01) {
					sys_exit(this->bx);
					break;
				}
			}
		}
	}
	
	unsigned char Runtime::getNextByte() {
		return this->data[++this->pc];
	}

	void Runtime::sys_exit(int code) {
		this->retCode = code;
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
	}

} // namespace VM