#ifndef _bytecode_h_
#define _bytecode_h_

#include <vector>
#include "BytecodeInt.h"
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
    vector<Bytecode*> rstack;        //runtime stack
    vector<int> fstack;         // frame stack

	int converttoInt(vector<unsigned char> arr, int pc);

	void pushi(BytecodeInt *B);
};

#endif 