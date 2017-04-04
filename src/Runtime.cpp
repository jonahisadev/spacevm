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