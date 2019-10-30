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
	int byteSwitch(int code,int index);
	void interpreter(int size);

	vector<unsigned char> mem;
	int sp;         //stackpointer
    int pc;        // program counter
    int fpsp;
    vector<Datatype*> rstack;        //runtime stack
    vector<int> fpstack;         // frame stack

	int convertToInt(vector<unsigned char> arr, int pc);
	float convertToFloat(vector<unsigned char> arr, int pc);
	short convertToShort(vector<unsigned char> arr, int pc);
	char convertToChar(vector<unsigned char> arr, int pc);

	void printstack(); // delete later

	void cmpe(int index);
	void cmplt(int index);
	void cmpgt(int index);
	void jmp(int index);
	void jmpc(int index);
	void call(int index);
	void ret(int index);
	void pushc(int index);
	void pushs(int index);
	void pushi(int index);
	void pushf(int index);
	void pushvc(int index);
	void pushvs(int index);
	void pushvi(int index);
	void pushvf(int index);
	void popm(int index);
	void popv(int index); 
	void popa(int index);
	void peekc(int index);
	void peeks(int index);
	void peeki(int index);
	void peekf(int index);
	void pokec(int index);
	void pokes(int index);
	void pokei(int index);
	void pokef(int index);
	void swp();
	void add();
	void sub();
	void mul();
	void div();
	void printc();
	void prints();
	void printi();
	void printf();
	void halt(int index);
};

#endif 