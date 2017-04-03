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
		int opcode = 0;

		while (opcode != ByteInst::HLT_) {
			opcode = this->data[++this->pc];

			// Implement fast runtime
		}
	}

	void Runtime::sys_exit(int code) {
		this->retCode = code;
	}

} // namespace VM