#ifndef SPACE_RUNTIME_H
#define SPACE_RUNTIME_H

#include <iostream>
#include <cmath>

#include <VM/Bytecode.h>

namespace VM {

	class Runtime {
	private:
		int retCode;

		short ax, bx, cx, dx, xx, yx = 0;
		short cf, cy, sp, bp, rm = 0;
		short pc = -1;

		unsigned char* data;

		void sys_exit(int code);
		void sys_print_b(unsigned char b);
		void sys_print_c(char c);

	public:
		Runtime(unsigned char* data);
		~Runtime();

		void start();
		unsigned char getNextByte();

		int getReturnCode() const { return retCode; }

		short* getRegister(unsigned char reg);
	};

} // namespace VM

#endif // SPACE_RUNTIME_H