# SpaceVM Documentation

## Table of Contents

* [Compiler Chain](#compiler-chain)
* [Basic Syntax](#basic-syntax)
* [Instruction Set](#instruction-set)
* [System Interrupts](#system-interrupts)
* [Debug Commands](#debug-commands)
* [Registers](#registers)
* [Memory Layout](#memory-layout)
* [Binary Header Layout](#binary-header-layout)
* [Limitations](#limitations)

---

## Compiler Chain

Before learning how to code in SpaceVM assembly, an understanding of what is
happening behind the scenes may be of some help. The compiler chain is broken
down into two main steps.

#### Parser (Tokenizer)

The parser takes the text and converts them into tokens. Currently almost all
token types have some sort of identifier in the text to be written in the
source code. The parser is not smart. A basic lexer is in place, and checks
against certain identifiers or keywords for instructions. The parser creates
tokens for each item it finds.

The tokens can take a token type, and an integer of data. The data can be better
determined by the token type. For instance, the data could be `2` which seems
very arbitrary. However, if the token is an instruction, as denoted by its type,
that would be equivalent to the `SUB` instruction. If the token is a number, 
that would just be the number 2.

As the tokens can only have an integer for their data, strings, labels, jumps,
calls, and variables must be saved in lists, where the data for that token is
the index in that list where the string can be found.

#### Compiler

After the token list is complete, the compiler is handed that list, and begins
to do its work. The compiler recognizes certain sequences of tokens, and
writes to a data buffer the according bytecode. Once the end of the token list
has been reached, the compiler writes the bytecode to a binary file, ready for
the runtime.

The compiler has a sort of semantics checker, which can be programmed into
the compiler by hand. It wouldn't make sense to subtract a number from an
instruction, so the compiler makes sure that doesn't happen. The compiler 
also matches the list indexes to the lists, and writes addresses accordingly, 
taking into account data sizes, and offsets.

---

## Basic Syntax

Read the following code:

```
#entry main

main:
	mov %ax $1
	mov %bx $42
	sysi
```

A couple of things to note here:

* The `#` symbol signals a preprocessor (similar to C)
	* This preprocessor tells the compiler to start in `main` (default is
		`start`)
* The label `main` is defined with a colon after it, denoting its label
status
* `mov` and `sysi` are instructions. The compiler will recognize these.
* The `%` before `ax` and `bx` denote those items as registers
* The `$` before the `1` and `42` denotes those items as numbers

The above code runs the `exit()` system call, which takes the `BX` register's
value and returns from the program with that number. In this case, `42` is
returned from the program when run.

Some more syntactical notes:

* Calling or jumping to a label needs `@` in front of the label name
* Variables are denoted by a `*` leading the name
* Getting the address of a variable require a leading `&`
* Comments are allowed, and like x86 assembly, requires a leading `;`
* Strings must be surrounded by double quotes: `"Hello world!"`

To see more examples of these, please look at `strings.vm` in the root
directory of the repository. You are allowed to reference instructions and
registers with capital letters. Variables and labels are case sensitive.

---

## Instruction Set

Legend:
* R = Register
* N = Number
* A = Address
* V = Variable
* L = Label
* 0 = No arguments

**_Remember:_** Arguments are NOT separated by commas in code

| Instruction 	| Arguments 			| Description 		|
| ------------- | --------------------- | ----------------- |
| `MOV`		  	| R,R / R,N / R,A		| Move a value to a register |
| `ADD`		  	| R,R / R,N				| Add a value into a register |
| `SUB`		  	| R,R / R,N				| Subtract a value into a register |
| `CALL`		| L						| Call a routine (routine must return) |
| `RET`			| 0						| Return from a routine call |
| `SYSI`		| 0						| Run a system interrupt |
| `MUL`			| R,R / R,N				| Multiply a value into a register |
| `DIV`			| R,R / R,N				| Divide a value into a register (remainder goes in RM register) |
| `SXR`			| R						| Shift a register right |
| `SXL`			| R						| Shift a register left |
| `INC`			| R						| Increment a register |
| `DEC`			| R						| Decrement a register |
| `PUSH`		| R / N					| Push a byte to the stack |
| `POP`			| R / 0					| Pop a byte from the stack |
| `CMP`			| R,R / R,N				| Compare two values (sets flags) |
| `JMP`			| L						| Jump unconditionally to a label |
| `JNE`			| L						| Jump if not equal |
| `JE`			| L						| Jump if equal |
| `JG`			| L						| Jump if greater than |
| `JL`			| L						| Jump if less than |
| `JGE`			| L						| Jump if greater than or equal |
| `JLE`			| L						| Jump if less than or equal |
| `JZ`			| L						| Jump if difference is zero |
| `JNZ`			| L						| Jump if difference is not zero |
| `PUSHW`		| R / N					| Push a word to the stack |
| `POPW`		| R / 0					| Pop a word from the stack |
| `AND`			| R,R / R,N				| AND two values into a register |
| `OR`			| R,R / R,N				| OR two values into a register |
| `XOR`			| R,R / R,N				| XOR two values into a register |
| `HLT`			| 0						| Terminate the program immediately |
| `PTR`			| R / R,R				| Dereference a pointer either into a separate register or into the same one |
| `STB`			| V,N					| Store a byte |
| `LDB`			| R,A					| Load byte into register |
| `STW`			| V,N					| Store word |
| `LDW`			| R,A					| Load word into register |
| `STR`			| V,STR					| Store a string |
| `PUSHA`		| 0						| Pushes all general purpose registers |
| `POPA`		| 0						| Pops values back into genereal purpose registers |
| `ADDW`		| R,N					| Add a 16-bit number to register |
| `SUBW`		| R,N					| Subtract a 16-bit number from register |
| `MULW`		| R,N					| Multiply a register by a 16-bit number |
| `DIVW`		| R,N					| Divide a registery by a 16-bit number |

---

## System Interrupts

| Interrupt 	| Arguments (BX, CX, ...) 	| Description 		|
| ------------- | ------------------------- | ----------------- |
| `0x01`		| `exit_code`				| Exit the program |
| `0x02`		| `byte`					| Print a byte to console |
| `0x03`		| `char`					| Print a char to console |
| `0x04`		| `word`					| Print a word to console |

---

## Debug Commands

| Command		| Arguments					| Description		|
| ------------- | ------------------------- | ----------------- |
| `bp` / `breakpoint`| addr					| Set a breakpoint to an address in compiled code |
| `r` / `run`	|							| Begin the runtime |
|				|							|					|
| `s` / `step`	|							| Step by instructions |
| `c` / `continue` |						| Continue running until a breakpoint is hit |
| `reg` / `registers` |						| Show general purpose and remainder registers |
| `sf` / `stack`| addr						| Show 256 bytes of memory from provided starting address |

---

## Registers

| Name			| Description			|
| ------------- | --------------------- |
| `AX, BX, CX, DX, XX, YX` | General purpose registers |
| `RM`			| Remainder |
| `BP`			| Base pointer |
| `SP`			| Stack pointer |
| `CF`			| Compare flags |

---

## Memory Layout

The below table assumes the base of the runtime memory is at the bottom, and
the max is at the top. There is no padding between the specific areas of
memory. Offsets are set in the runtime header. The addresses listed are the
bases of each section. It should be noted that the stack grows upward instead
of downwards. Because I'm lazy.

| Address 	| Description 	|
| --------- | ------------- |
| `0x10000`	| MAX			|
| `0xF000`	| Reserved		|
| `0xE000`	| Video Memory (Not used) |
| `0x8000`	| Stack 		|
| `0x4000`	| Variables		|
| `0x1000`	| Program		|
| `0x0000`	| BASE			|

---

## Binary Header Layout

The first 8 bytes of the compiled binary are very important, and are required
for a proper runtime. It should be noted that the last six bytes of the header
are replaced by `NOP` if their features are not required.

### 0-1

The first two bytes are simply the length of the binary file written in
big-endian format. The official SpaceVM runtime loads the length to prevent
memory corruption from destroying the loaded binary.

### 2-4

The next three bytes are actual instructions for the runtime, which is a call
instruction to where the data is loaded. After loading all of the data onto
the stack from instructions such as `STB` and `STW`, there is a `RET` 
instruction, which returns back to the last three bytes of the header. Data
loading addressing is performed by the compiler, and not the programmer.

### 5-7

The last three bytes are also instructions for the runtime. If an entry point
to a label is specified by the programmer, a jump instruction to the address of
that label is written there.

---

## Limitations

* The current system is 16-bit. Values over 0xFFFF or 65535 will probably break 
the system (unless you combine registers by some sort of magic)
* While the current system is 16-bit, most instructions are 8-bit. To get a
16-bit number in a register, a word must be pushed, and popped back into the
register.
* Only include files one time. Any extra time will create duplicate symbols
* Some syntactical and/or semantic errors may not give all necessary
information to properly debug the issue.

---