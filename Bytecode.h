#ifndef _bytecode_h_
#define _bytecode_h_

#include <vector>
#include "Datatype.h"

using namespace std;

class Bytecode{
public:
	
	Bytecode();
	Bytecode(vector<unsigned char> mem,int size);
	virtual ~Bytecode();
	//int byteSwitch(int code,int index);
	void byteSwitch(int code);
	void interpreter(int size);

	vector<unsigned char> mem;
	int sp;         //stackpointer
    int pc;        // program counter
    int fpsp;
    vector<Datatype*> rstack;        //runtime stack
    vector<int> fpstack;         // frame stack

	//int convertToInt(vector<unsigned char> arr, int pc);
	//float convertToFloat(vector<unsigned char> arr, int pc);
	//short convertToShort(vector<unsigned char> arr, int pc);
	//char convertToChar(vector<unsigned char> arr, int pc);
	int convertToInt();
	float convertToFloat();
	short convertToShort();
	char convertToChar();

	void printstack(); // delete later

	void cmpe();
	void cmplt();
	void cmpgt();
	void jmp();
	void jmpc();
	void call();
	void ret();
	void pushc();
	void pushs();
	void pushi();
	void pushf();
	void pushvc();
	void pushvs();
	void pushvi();
	void pushvf();
	void popm();
	void popv(); 
	void popa();
	void peekc();
	void peeks();
	void peeki();
	void peekf();
	void pokec();
	void pokes();
	void pokei();
	void pokef();
	void swp();
	void add();
	void sub();
	void mul();
	void div();
	void printc();
	void prints();
	void printi();
	void printf();
	void halt();
};

#endif 