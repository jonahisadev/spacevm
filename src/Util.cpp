#include <VM/Util.h>

namespace VM {
    
    char* Util::readFile(CONST char* path) {
        FILE* file = fopen(path, "r");
        ASSERT(file, "Could not open file");
        
        fseek(file, 0, SEEK_END);
        int size = (int) ftell(file);
        fseek(file, 0, SEEK_SET);
        
        char* data = new char[size];
        ASSERT(data, "Could not load file");
        
        fread(data, 1, size, file);
        fclose(file);
        
        return data;
    }
    
} // namespace VM