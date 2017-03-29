#include <VM/Compiler.h>

namespace VM {

	Compiler::Compiler(TokenList* tokenList) {
		this->tokenList = tokenList;
	}

	Compiler::~Compiler() {
		// Nothing
	}

	void Compiler::start() {
		std::cout << "Will begin compiling!" << std::endl;
	}

}