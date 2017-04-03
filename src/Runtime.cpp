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

			if (opcode == ByteInst::MOV_RN) {
				unsigned char reg = this->data[++this->pc];
				unsigned char val = this->data[++this->pc];
				setRegister(reg, val);
				continue;
			}
			
			if (opcode == ByteInst::SYSI_) {
				if (this->ax == 0x01) {
					sys_exit(this->bx);
					break;
				}
			}
		}
	}

	void Runtime::sys_exit(int code) {
		this->retCode = code;
	}
	
	void Runtime::setRegister(unsigned char reg, unsigned char val) {
		if (reg == ByteReg::AX_) {
			this->ax = (short)val;
		}
		else if (reg == ByteReg::BX_) {
			this->bx = (short)val;
		}
	}

} // namespace VM