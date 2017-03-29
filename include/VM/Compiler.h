#ifndef SPACE_COMPILER_H
#define SPACE_COMPILER_H

#include <cstdlib>
#include <iostream>

#include <VM/Util.h>
#include <VM/Token.h>

namespace VM {

	enum ByteInst {
		MOV_RL = 0x01
	};

	class Compiler {
	private:
		TokenList* tokenList;

	public:
		Compiler(TokenList* tokenList);
		~Compiler();

		void start();
	};

}

#endif // SPACE_COMPILER_H