#ifndef SPACE_RUNTIME_H
#define SPACE_RUNTIME_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <VM/Util.h>
#include <VM/Bytecode.h>
#include <VM/Register.h>
#include <VM/Debugger.h>

namespace VM {

	class Runtime {
	private:
		int retCode;
		const int MEMORY_SIZE = 0x10000;
		const int PROG_BASE = 0x1000;
		const int STACK_MAX = 0xE000;
		const int VAR_OFFSET = 0x4000;
		
		Register* ax = new Register(ByteReg::AX_);
		Register* bx = new Register(ByteReg::BX_);
		Register* cx = new Register(ByteReg::CX_);
		Register* dx = new Register(ByteReg::DX_);
		Register* xx = new Register(ByteReg::XX_);
		Register* yx = new Register(ByteReg::YX_);
		Register* rm = new Register(ByteReg::RM_);
		
		unsigned short cf = 0b0000;
		unsigned short sp = 0x8000-1;
		unsigned short pc = PROG_BASE + 2;

		unsigned short var_ptr = 0;
		
		unsigned char* memory;

		void sys_exit(int code);
		void sys_print_b(unsigned char b);
		void sys_print_c(char c);
		void sys_print_w(short w);
		
		bool debug = false;

	public:
		Runtime(unsigned char* data);
		~Runtime();

		void start();
		unsigned char getNextByte();
		
		void push(unsigned char data);
		unsigned char pop();
		void pushw(short data);
		short popw();
		
		// 0001 = Equals
		// 0010 = Less than
		// 0100 = Greater than
		// 1000 = Zero
		void cmp(short a, short b);
		void jump();
		bool getFlag(int ptr);

		int getReturnCode() const { return retCode; }
		void setDebug(bool debug) { this->debug = debug; }
		
		// Debug Functions
		void printRegisters();
		void printStack(unsigned short addr);

		Register* getRegister(unsigned char reg);
	};

} // namespace VM

#endif // SPACE_RUNTIME_H