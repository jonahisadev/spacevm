#include <VM/Common.h>
#include <VM/Util.h>

int main(int argc, char** argv) {
    char* fileContents = VM::Util::readFile("Makefile");
    ASSERT(fileContents, "Intentional nullptr");
    return 0;
}