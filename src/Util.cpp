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
    
    int Util::strLength(char* a) {
        int len = 0;
        while (a[len] != '\0')
            len++;
        return len;
    }
    
    bool Util::strEquals(char* a, char* b) {
        int aLen = strLength(a);
        int bLen = strLength(b);
        
        if (aLen != bLen)
            return false;
            
        for (int i = 0; i < aLen; i++) {
            if (a[i] != b[i])
                return false;
        }
        
        return true;
    }
    
} // namespace VM