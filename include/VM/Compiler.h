#ifndef SPACE_COMPILER_H
#define SPACE_COMPILER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <VM/Util.h>
#include <VM/Token.h>
#include <VM/List.h>
#include <VM/Bytecode.h>

namespace VM {

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