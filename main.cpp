#include <VM/Common.h>
#include <VM/Util.h>
#include <VM/Parser.h>
#include <VM/Token.h>
#include <VM/Compiler.h>
#include <VM/Runtime.h>

void showHelp() {
	std::cout << "== SpaceVM Help ==" << std::endl;
	std::cout << "\tspc -c [file]: Compile source" << std::endl;
	std::cout << "\tspc -r [file]: Run bytecode" << std::endl;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		showHelp();
		return 1;
	}

	if (VM::Util::strEquals(argv[1], "-c")) {
	    char* fileContents = VM::Util::readFile(argv[2]);
	    ASSERT(fileContents, "File reading failure");

		VM::Parser* p = new VM::Parser(fileContents);
		p->start();
		p->showTokenList();

		VM::Compiler* c = p->createCompiler(std::string(argv[2]).append("c").c_str());
		c->start();

		delete p;
		delete c;

		return 0;
	}

	else if (VM::Util::strEquals(argv[1], "-r")) {
		unsigned char* data = VM::Util::readBinFile(argv[2]);
		ASSERT(data, "Binary reading failure");

		VM::Runtime* r = new VM::Runtime(data);
		r->start();

		int ret = r->getReturnCode();
		delete r;

		return ret;
	}
}