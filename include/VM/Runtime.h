#ifndef SPACE_RUNTIME_H
#define SPACE_RUNTIME_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <VM/Util.h>
#include <VM/Bytecode.h>

namespace VM {

	class Runtime {
	private:
		int retCode;
		const int MEMORY_SIZE = 0x10000;
		const int STACK_MAX = 0xE000;
		const int VAR_OFFSET = 0x4000;

		short ax, bx, cx, dx, xx, yx = 0;
		short rm = 0;
		unsigned short cf = 0b0000;
		unsigned short sp = 0x8000-1;
		unsigned short pc = 0;

		unsigned short var_ptr = 0;

		unsigned char* data;
		unsigned char* memory;

		void sys_exit(int code);
		void sys_print_b(unsigned char b);
		void sys_print_c(char c);
		void sys_print_w(short w);

	public:
		Runtime(unsigned char* data);
		~Runtime();

		void start();
		unsigned char getNextByte();
		void push(unsigned char data);
		short pop();
		
		// 0001 = Equals
		// 0010 = Less than
		// 0100 = Greater than
		// 1000 = Zero
		void cmp(short a, short b);
		bool getFlag(int ptr);

		int getReturnCode() const { return retCode; }

		short* getRegister(unsigned char reg);
	};

} // namespace VM

#endif // SPACE_RUNTIME_H