#ifndef SPACE_RUNTIME_H
#define SPACE_RUNTIME_H

#include <iostream>

#include <VM/Bytecode.h>

namespace VM {

	class Runtime {
	private:
		int retCode;
		
		short ax, bx, cx, dx, xx, yx;
		short sp, bp;
		short pc = -1;

		unsigned char* data;

	public:
		Runtime(unsigned char* data);
		~Runtime();

		void start();
		unsigned char getNextByte();

		void sys_exit(int code);

		int getReturnCode() const { return retCode; }
		
		short* getRegister(unsigned char reg);
	};

} // namespace VM

#endif // SPACE_RUNTIME_H