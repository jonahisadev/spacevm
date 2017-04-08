#ifndef SPACE_TOKEN_H
#define SPACE_TOKEN_H

#include <iostream>
#include <cstdlib>

#include <VM/Util.h>

namespace VM {

	enum class TokenType {
		INST,
		REG,
		NUM,
		LBL,
		JMP_T,
	};

	enum TokenInst {
		MOV,
		ADD,
		SUB,
		CALL,
		RET,
		SYSI,
		MUL,
		DIV,
		SXR,
		SXL,
		INC,
		DEC,
		PUSH,
		POP,
		CMP,
		JMP,
		JL,

		HLT
	};

	enum TokenReg {
		AX, BX, CX, DX, XX, YX,
		AL, BL, CL, DL, XL, YL,
		AH, BH, CH, DH, XH, YH,
		CF, CY, BP, SP, RM, PC
	};

	class Token {
	private:
		TokenType type;
		int data;

	public:
		Token(TokenType type, int data);
		~Token();

		TokenType getType() const { return type; }
		int getData() const { return data; }

		LOCAL const char* getInstruction(int inst);
		LOCAL const char* getRegister(int reg);
		LOCAL int convertNumber(char* str);

		LOCAL int getRegToken(char* reg);
	};

	class TokenList {
	private:
		Token** data;
		int ptr;
		int size;

	public:
		TokenList(int size);
		~TokenList();

		void add(Token* t);
		Token* get(int ptr);

		void showList();

		int getPointer() const { return ptr; }
	};

} // namespace VM

#endif // SPACE_TOKEN_H