#ifndef SPACE_COMPILER_H
#define SPACE_COMPILER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <VM/Util.h>
#include <VM/Token.h>
#include <VM/List.h>

namespace VM {

	enum ByteInst {
		NOP =		0x00,
		MOV_RN =	0x01,

		ADD_RN =	0x04,
		
		SUB_RN =	0x07,
		
		CALL_ = 	0x0A,
		RET_ =		0x0B,
		SYSI_ = 	0x0C,
		
		MUL_RN =	0x10,
	};

	enum ByteReg {
		AX_ = 0x00,
		BX_ = 0x01,
		CX_ = 0x02,
		DX_ = 0x03,
		XX_ = 0x04,
		YX_ = 0x05,

		AL_ = 0x10,
		BL_ = 0x11,
		CL_ = 0x12,
		DL_ = 0x13,
		XL_ = 0x14,
		YL_ = 0x15,

		AH_ = 0x20,
		BH_ = 0x21,
		CH_ = 0x22,
		DH_ = 0x23,
		XH_ = 0x24,
		YH_ = 0x25,

		CF_ = 0x30,
		CY_ = 0x31,
		BP_ = 0x32,
		SP_ = 0x33,
		RM_ = 0x34
	};

	class Compiler {
	private:
		TokenList* tokenList;
		ByteList* textBuf;
		IntList* addrList;
		int addr;
		
		const char* path;

	public:
		Compiler(const char* path, TokenList* tokenList);
		~Compiler();

		void start();
		void writeByte(unsigned char data);
	
		void writeOutputFile();
		
		unsigned char getByteReg(int tokenData);
	};

} // namespace VM

#endif // SPACE_COMPILER_H