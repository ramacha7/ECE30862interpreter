#include <vector>
#include "BytecodeInt.h"
using namespace std;

class Bytecode{
public:
	enum Type{Char,Short,Int,Float};
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

	void pushi(BytecodeInt B);
};