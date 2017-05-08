#include <VM/Register.h>

namespace VM {
	
	Register::Register(int id) {
		this->id = id;
		this->data = 0;
		this->ref = RegRef::R_FULL;
	}
	
	Register::~Register() {
		// Nothing for now
	}
	
	void Register::setReferenceType(RegRef ref) {
		this->ref = ref;
	}
	
	void Register::set(short data) {
		if (this->ref == RegRef::R_HIGH) {
			unsigned char* sections = Util::sToB(data);
			*((unsigned char*)&this->data + 1) = sections[1];
		} else if (this->ref == RegRef::R_LOW) {
			unsigned char* sections = Util::sToB(data);
			*((unsigned char*)&this->data) = sections[1];
		} else if (this->ref == RegRef::R_FULL) {
			this->data = data;
		}
	}
	
	short Register::get() {
		return this->data;
	}
	
} // namespace VM