#include <VM/Common.h>
#include <VM/Util.h>
#include <VM/Parser.h>
#include <VM/Token.h>
#include <VM/Compiler.h>

int main(int argc, char** argv) {
    char* fileContents = VM::Util::readFile("test.vm");
    ASSERT(fileContents, "File reading failure");

	VM::Parser* p = new VM::Parser(fileContents);
	p->start();
	p->showTokenList();

	VM::Compiler* c = p->createCompiler();
	c->start();

	delete p;
	delete c;

    return 0;
}