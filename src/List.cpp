#include <VM/List.h>

namespace VM {
    
    ByteList::ByteList(int size) {
        this->data = (unsigned char*) malloc(sizeof(unsigned char) * size);
        this->size = size;
        this->ptr = 0;
    }
    
    ByteList::~ByteList() {
        free(data);
    }
    
    void ByteList::add(unsigned char data) {
        if (this->ptr >= this->size) {
            this->size *= 2;
            this->data = (unsigned char*) realloc(this->data, sizeof(unsigned char) * this->size);
        }
        
        this->data[this->ptr++] = data;
    }
    
    unsigned char ByteList::get(int ptr) {
        return this->data[ptr];
    }
    
} // namespace VM