#include <VM/Common.h>
#include <VM/Util.h>
#include <VM/Parser.h>
#include <VM/Token.h>
#include <VM/Compiler.h>
#include <VM/Runtime.h>
#include <VM/Decomp.h>

void showHelp() {
	std::cout << "== SpaceVM Help ==" << std::endl;
	std::cout << "\tspc -c [file] (-d/-g): Compile source" << std::endl;
	std::cout << "\tspc -r [file]: Run bytecode" << std::endl;
	std::cout << "\tspc -d [file]: Disassemble bytecode" << std::endl;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		showHelp();
		return 1;
	}

	if (VM::Util::strEquals(argv[1], "-c")) {
		char* path = VM::Util::strDupFull(argv[2]);
	    char* fileContents = VM::Util::readFile(path);
		
		int flen = VM::Util::strLength(fileContents);
	    ASSERT(fileContents, "File reading failure");

		VM::Parser* p = new VM::Parser(fileContents, flen);
		
		// TODO: Make this more efficient
		if (argc >= 4 && VM::Util::strEquals(argv[3], "-d"))
			p->setDebug(true);
		if (argc >= 4 && VM::Util::strEquals(argv[3], "-g"))
			p->setSymbols(true);
			
		p->start();

		if (p->isDebug()) {
			p->showTokenList();
			p->showLabelLists();
		}
			
		// make output path constant	
		std::string temp = std::string(path);
		temp.append("c");
		const char* outPath = temp.c_str();
		VM::Compiler* c = p->createCompiler(outPath);
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
	
	else if (VM::Util::strEquals(argv[1], "-d")) {
		unsigned char* data = VM::Util::readBinFile(argv[2]);
		ASSERT(data, "Binary reading failure");
		
		// Load symbols file
		char* debugFile = VM::Util::strDupFull(argv[2]);
		debugFile[VM::Util::strLength(debugFile)-1] = 'd';
		char* symbols = VM::Util::readFile(debugFile);
		
		VM::Decomp* d;
		if (symbols) {
			d = new VM::Decomp(data, true, symbols);
		} else {
			d = new VM::Decomp(data, false, nullptr);
		}
		d->start();
		
		delete[] debugFile;
		delete[] symbols;
		
		return 0;
	}
}