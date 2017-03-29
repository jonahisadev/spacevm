#ifndef SPACE_COMPILER_H
#define SPACE_COMPILER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <VM/Util.h>
#include <VM/Token.h>

namespace VM {

	enum ByteInst {
		MOV_RN = 0x01,
	};

	enum ByteReg {
		AX_ = 0x01,
		BX_ = 0x02
	};

	class Compiler {
	private:
		TokenList* tokenList;
		FILE* obj_file;

	public:
		Compiler(const char* path, TokenList* tokenList);
		~Compiler();

		void start();
		void writeByte(unsigned char data);
	};

}

#endif // SPACE_COMPILER_H