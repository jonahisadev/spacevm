#ifndef SPACE_DECOMP_H
#define SPACE_DECOMP_H

#include <VM/Bytecode.h>
#include <VM/Util.h>
#include <VM/Token.h>

namespace VM {
	
	class Decomp {
	private:
		unsigned char* data;
		
	public:
		Decomp(unsigned char* data);
		~Decomp();
		
		void start();
	};
	
} // namespace VM

#endif // SPACE_DECOMP_H