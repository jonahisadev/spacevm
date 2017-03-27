#include <VM/Common.h>
#include <VM/Util.h>

int main(int argc, char** argv) {
    char* fileContents = VM::Util::readFile("Makefile");
    ASSERT(fileContents, "File reading failure");
    
    std::cout << fileContents << std::endl;
    
    return 0;
}