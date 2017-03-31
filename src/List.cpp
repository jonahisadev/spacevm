#include <VM/List.h>

namespace VM {
    
    //
    //  BYTE LIST
    //
    
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
    
    //
    //  INT LIST
    //
    
    IntList::IntList(int size) {
        this->data = (int*) malloc(sizeof(int) * size);
        this->size = size;
        this->ptr = 0;
    }
    
	IntList::~IntList() {
	    free(this->data);
	}
	
	void IntList::add(int data) {
	    if (this->ptr >= this->size) {
	        this->size *= 2;
	        this->data = (int*) realloc(this->data, sizeof(int) * this->size);
	    }
	    
	    this->data[this->ptr++] = data;
	}
	
	int IntList::get(int ptr) {
	    return this->data[ptr];
	}
    
} // namespace VM