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
		unsigned short addr;
		
		List<char*>* lblList;
		List<char*>* jmpList;
		List<char*>* addrList;
		List<char*>* varList;
		List<char*>* strList;
		
		Map<int, unsigned short>* lblMap;
		Map<int, unsigned short>* jmpMap;
		Map<int, unsigned short>* addrMap;
		Map<int, unsigned short>* varMap;

		const char* path;
		const char* beginLabel;
		
		void serror(const char* inst, int line);
		
		bool currentDataSection = false;

	public:
		Compiler(const char* path, TokenList* tokenList);
		~Compiler();

		void setLabelList(List<char*>* lblList);
		void setJumpList(List<char*>* jmpList);
		void setAddrList(List<char*>* addrList);
		void setVarList(List<char*>* varList);
		void setStrList(List<char*>* strList);
		void setBeginLabel(const char* beginLabel);

		void start();
		void writeByte(unsigned char data);

		void writeOutputFile();

		unsigned char getByteReg(int tokenData);
	};

} // namespace VM

#endif // SPACE_COMPILER_H