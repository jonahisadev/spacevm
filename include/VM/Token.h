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
		PPI,
		ADDR,
		VAR,
		STRING,
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
		JNE,
		JE,
		JG,
		JL,
		JGE,
		JLE,
		JZ,
		JNZ,
		AND,
		OR,
		XOR,
		
		PTR,
		STB,
		LDB,
		STW,
		LDW,
		STR,

		HLT
	};

	enum TokenReg {
		AX, BX, CX, DX, XX, YX,
		AL, BL, CL, DL, XL, YL,
		AH, BH, CH, DH, XH, YH,
		CF, CY, BP, SP, RM, PC
	};
	
	enum TokenPPI {
		DATA,
		END,
		ENTRY,
		INCLUDE,
	};

	class Token {
	private:
		TokenType type;
		int data;
		int line;

	public:
		Token(TokenType type, int data, int line);
		~Token();

		TokenType getType() const { return type; }
		int getData() const { return data; }
		int getLine() const { return line; }
		
		void setData(int data) { this->data = data; }

		LOCAL const char* getInstruction(int inst);
		LOCAL const char* getRegister(int reg);
		LOCAL int convertNumber(char* str, int base);

		LOCAL int getRegToken(char* reg, int line);
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
		void appendList(TokenList* list);

		void showList();

		int getPointer() const { return ptr; }
	};

} // namespace VM

#endif // SPACE_TOKEN_H