#ifndef SPACE_LIST_H
#define SPACE_LIST_H

#include <iostream>
#include <cstdlib>

namespace VM {
    
	template <class T>
	class List {
	private:
		T* data;
		int size;
		int ptr;
		
	public:
		List(int size);
		~List();
		
		void add(T data);
		T get(int ptr) const { return data[ptr]; }
		void set(int ptr, T data);
		void showList();
		
		int getPointer() const { return ptr; }
	};
	
	template class List<unsigned char>;
	template class List<int>;
	template class List<char*>;
	
	template <class T>
	List<T>::List(int size) {
		this->data = (T*) malloc(sizeof(T) * size);
		this->size = size;
		this->ptr = 0;
	}
	
	template <class T>
	List<T>::~List() {
		free(this->data);
	}
	
	template <class T>
	void List<T>::add(T data) {
		if (this->ptr >= this->size) {
			this->size *= 2;
			this->data = (T*) realloc(this->data, sizeof(T) * this->size);
		}
		
		this->data[this->ptr++] = data;
	}
	
	/**
	template <class T>
	T List<T>::get(int ptr) {
		return this->data[ptr];
	}
	**/
	
	template <class T>
	void List<T>::set(int ptr, T data) {
		this->data[ptr] = data;
	}
	
	template <class T>
	void List<T>::showList() {
		for (int i = 0; i < getPointer(); i++) {
			std::cout << this->data[i];
			if (i != getPointer() - 1)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}
    
} // namespace VM

#endif // SPACE_LIST_H