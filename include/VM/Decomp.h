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

		// Used for runtime debugger
		bool hijacked = false;
		unsigned short* h_addr;

		
	public:
		Decomp(unsigned char* data, bool hasSymbols, char* symbols);
		~Decomp();
		
		void start();
		void loadSymbols();
		void printJumpLabel(unsigned char a, unsigned char b);
		void hijack(unsigned short* addr);
	};
	
} // namespace VM

#endif // SPACE_DECOMP_H