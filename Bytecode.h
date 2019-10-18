#include <vector>
using namespace std;

class Bytecode{
public:
	Bytecode();
	Bytecode(unsigned char * mem,int size);
	virtual ~Bytecode();
	int byteSwitch(unsigned char code);

	unsigned char * mem;
	int sp;         //stackpointer
    int pc;        // program counter
    int fpsp;
    vector<Bytecode*> rstack;        //runtime stack
    vector<int> fstack;         // frame stack
};