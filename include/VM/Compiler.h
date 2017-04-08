#ifndef SPACE_COMPILER_H
#define SPACE_COMPILER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <VM/Util.h>
#include <VM/Token.h>
#include <VM/List.h>
#include <VM/Map.h>
#include <VM/Bytecode.h>

namespace VM {

	class Compiler {
	private:
		TokenList* tokenList;
		List<unsigned char>* textBuf;
		int addr;
		
		List<char*>* lblList;
		List<char*>* jmpList;
		
		Map<int, unsigned short>* lblMap;
		Map<int, unsigned short>* jmpMap;

		const char* path;

	public:
		Compiler(const char* path, TokenList* tokenList);
		~Compiler();

		void setLabelList(List<char*>* lblList);
		void setJumpList(List<char*>* jmpList);

		void start();
		void writeByte(unsigned char data);

		void writeOutputFile();

		unsigned char getByteReg(int tokenData);
	};

} // namespace VM

#endif // SPACE_COMPILER_H