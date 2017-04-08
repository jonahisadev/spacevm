#ifndef SPACE_MAP_H
#define SPACE_MAP_H

namespace VM {
    
    template <class A, class B>
    class Map<A, B> {
    private:
        A* dataA;
        B* dataB;
        
        int size;
        int ptr;
        
    public:
        Map(int size);
        ~Map();
        
        void add(A dataA, B dataB);
        A getA(int ptr);
        B getB(int ptr);
        void showList();
        
        int getPointer() const { return ptr; }
    };
    
    template class Map<int, unsigned short>;    // index, address
    
    template <class A, class B>
    Map<A, B>::Map(int size) {
        this->dataA = (A*) malloc(sizeof(A) * size);
        this->dataB = (B*) malloc(sizeof(B) * size);
        this->size = size;
        this->ptr = 0;
    }
    
    template <class A, class B>
    Map<A, B>::~Map() {
        free(this->dataA);
        free(this->dataB);
    }
    
    template <class A, class B>
    void Map<A, B>::add(A dataA, B dataB) {
        if (this->ptr >= this->size) {
            this->size *= 2;
            this->dataA = (A*) realloc(this->dataA, this->size);
            this->dataB = (B*) realloc(this->dataB, this->size);
        }
        
        this->dataA[this->ptr] = dataA;
        this->dataB[this->ptr] = dataB;
        
        this->ptr++;
    }
    
    template <class A, class B>
    A Map<A, B>::getA(int ptr) {
        return this->dataA[ptr];
    }
    
    template <class A, class B>
    B Map<A, B>::getB(int ptr) {
        return this->dataB[ptr];
    }
    
    template <class A, class B>
    void Map<A, B>::showList() {
        // TODO: actually implement
    }
    
} // namespace VM

#endif // SPACE_MAP_H