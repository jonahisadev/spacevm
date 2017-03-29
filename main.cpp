#include <VM/Common.h>
#include <VM/Util.h>
#include <VM/Parser.h>
#include <VM/Token.h>

int main(int argc, char** argv) {
    char* fileContents = VM::Util::readFile("test.vm");
    ASSERT(fileContents, "File reading failure");

	VM::Parser* p = new VM::Parser(fileContents);
	p->start();
	p->showTokenList();

	delete p;
    return 0;
}