#ifndef SPACE_RUNTIME_H
#define SPACE_RUNTIME_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <VM/Bytecode.h>

namespace VM {

	class Runtime {
	private:
		int retCode;
		const int MEMORY_SIZE = 0x10000;
		const int STACK_MAX = 0xE000;

		short ax, bx, cx, dx, xx, yx = 0;
		short cf, cy, bp, rm = 0;
		unsigned short sp = 0x8000-1;
		short pc = -1;

		unsigned char* data;
		unsigned char* memory;

		void sys_exit(int code);
		void sys_print_b(unsigned char b);
		void sys_print_c(char c);

	public:
		Runtime(unsigned char* data);
		~Runtime();

		void start();
		unsigned char getNextByte();
		void push(unsigned char data);
		short pop();

		int getReturnCode() const { return retCode; }

		short* getRegister(unsigned char reg);
	};

} // namespace VM

#endif // SPACE_RUNTIME_H