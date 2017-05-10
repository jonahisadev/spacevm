#ifndef SPACE_DECOMP_H
#define SPACE_DECOMP_H

#include <VM/Bytecode.h>
#include <VM/Util.h>
#include <VM/Token.h>
#include <VM/Map.h>

namespace VM {
	
	class Decomp {
	private:
		unsigned char* data;
		char* symbols;
		bool hasSymbols = false;
		
		Map<int, char*>* symbolMap;
		
	public:
		Decomp(unsigned char* data);
		~Decomp();
		
		void start();
		
		void setSymbols(char* symbols) {
			this->symbols = symbols;
			hasSymbols = true;
		}
		
		void loadSymbols();
	};
	
} // namespace VM

#endif // SPACE_DECOMP_H