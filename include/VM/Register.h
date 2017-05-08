#ifndef SPACE_REGISTER_H
#define SPACE_REGISTER_H

#include <VM/Common.h>
#include <VM/Util.h>

namespace VM {
	
	enum class RegRef {
		R_HIGH,
		R_LOW,
		R_FULL
	};
	
	class Register {
	private:
		int id;
		short data;
		RegRef ref;
		
	public:
		Register(int id);
		~Register();
		
		void setReferenceType(RegRef ref);
		void set(short data);
		short get();
	};
	
} // namespace VM

#endif // SPACE_REGISTER_H