#ifndef SPACE_LIST_H
#define SPACE_LIST_H

#include <iostream>
#include <cstdlib>

namespace VM {
    
    class ByteList {
    private:
        unsigned char* data;
        int size;
        int ptr;
        
    public:
        ByteList(int size);
        ~ByteList();
        
        void add(unsigned char data);
        unsigned char get(int ptr);
        
        int getPointer() const { return ptr; }
    };
    
    class IntList {
    private:
    	int* data;
    	int size;
    	int ptr;
    	
    public:
    	IntList(int size);
    	~IntList();
    	
    	void add(int data);
    	int get(int ptr);
    	
    	int getPointer() const { return ptr; }
    };
    
} // namespace VM

#endif // SPACE_LIST_H