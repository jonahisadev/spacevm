#ifndef SPACE_BYTECODE_H
#define SPACE_BYTECODE_H

namespace VM {

	enum ByteInst {
		NOP =		0x00,
		MOV_RN =	0x01,
		MOV_RR =	0x02,
		MOV_RA = 	0x03,

		ADD_RN =	0x04,
		ADD_RR = 	0x05,

		SUB_RN =	0x07,
		SUB_RR = 	0x08,

		CALL_ = 	0x0A,
		RET_ =		0x0B,
		SYSI_ = 	0x0C,

		MUL_RN =	0x10,
		MUL_RR =	0x11,

		DIV_RN = 	0x13,
		DIV_RR = 	0x14,

		SXR_R = 	0x16,
		SXL_R = 	0x17,
		INC_R = 	0x18,
		DEC_R = 	0x19,

		PUSH_R = 	0x1A,
		PUSH_N = 	0x1B,
		POP_R = 	0x1C,
		POP_X = 	0x1D,
		
		CMP_RR = 	0x1E,
		CMP_RN = 	0x1F,
		JMP_ = 		0x20,
		JNE_ = 		0x21,
		JE_ = 		0x22,
		JG_ = 		0x23,
		JL_ = 		0x24,
		JGE_ = 		0x25,
		JLE_ = 		0x26,
		JZ_ = 		0x27,
		JNZ_ = 		0x28,
		
		PUSHW_R = 	0x2A,
		PUSHW_N = 	0x2B,
		POPW_R = 	0x2C,
		POPW_X =	0x2D,
		
		AND_RN = 	0x30,
		AND_RR = 	0x31,
		OR_RN = 	0x32,
		OR_RR =		0x33,
		XOR_RN = 	0x34,
		XOR_RR = 	0x35,

		HLT_ = 		0x40,
		
		PTR_R = 	0x50,
		PTR_RR = 	0x51,
		STB_ = 		0x52,
		LDB_ =		0x53,
		STW_ = 		0x54,
		LDW_ = 		0x55,
		STR_ =		0x56,
	};

	enum ByteReg {
		AX_, BX_, CX_, DX_, XX_, YX_,
		AL_, BL_, CL_, DL_, XL_, YL_,
		AH_, BH_, CH_, DH_, XH_, YH_,
		CF_, CY_, BP_, SP_, RM_, PC_
	};

} // namespace VM

#endif // SPACE_BYTECODE_H