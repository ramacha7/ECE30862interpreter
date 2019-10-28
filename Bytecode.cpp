#include "Bytecode.h"
#include "Datatype.h"
#include <iostream>
#include <vector>

using namespace std;

Bytecode::Bytecode(){}
Bytecode::~Bytecode(){}

Bytecode::Bytecode(vector<unsigned char> arr,int size)
{
	sp = -1;
	fpsp = -1;
	pc = 0;
	mem.reserve(size);
	mem = arr;

	interpreter(size);
}

void Bytecode::interpreter(int size)
{
	int i = 0;
	//size = 4;
	int offset = 0;
	while(i < size)
	{
		int code = (int)mem[i];
		offset = byteSwitch(code,i);

		i += offset;
		pc += offset;	
		printstack();
	}

}

int Bytecode::converttoInt(vector<unsigned char> arr, int pc)
{
	int i = (int)(arr[pc + 1] ^ (arr[pc + 2] << 8) ^ (arr[pc + 3] << 16) ^ (arr[pc + 4] << 24));
	return i;
}

int Bytecode::byteSwitch(int code,int index){
	switch(code){
		// case 132:
		// 	// convert
		// 	// make object
		// 	cmpe(); // compare (equal)
		// 	break;
		// case 136:
		// 	cmplt(); // compare (less than)
		// 	break;
		// case 140:
		// 	cmpgt(); // compare (greater than)
		// 	break;
		// case 36:
		// 	jmp(); // jump to location of runtime stack
		// 	break;
		// case 40:
		// 	jmpc(); // jump if next on rstack is 1
		// 	break;
		// case 44:
		// 	call(); // same fpstack and jump
		// 	break;
		// case 48:
		// 	ret(); // restore rstack pointer 
		// 	break;
		// case 68:
		// 	pushc(); // push char
		// 	break;
		// case 69:
		// 	pushs(); // push short
		// 	break;
		case 70:
			Datatype::Type t = Datatype::Int;
			pushi(t, index); // push int
			return 5;
			break;
		// case 71:
		// 	pushf(); // push float
		// 	break;
		// case 72:
		// 	pushvc(); // push variable char
		// 	break;
		// case 73:
		// 	pushvs(); // push variable short
		// 	break;
		// case 74:
		// 	pushvi(); // push variable int
		// 	break;
		// case 75:
		// 	pushvf(); // push variable float
		// 	break;
		// case 76:
		// 	popm(); // pop multiple values
		// 	break;
		// case 80:
		// 	popv(); // pop value into variable
		// 	break;
		// case 77:
		// 	popa(); // pop all top entries 
		// 	break;
		// case 84:
		// 	peekc(); // take char value at offset
		// 	break;
		// case 85:
		// 	peeks(); // take short value at offset
		// 	break;
		// case 86:
		// 	peeki(); // take int value at offset
		// 	break;
		// case 87:
		// 	peekf(); // take float value at offset
		// 	break;
		// case 88:
		// 	pokec(); // change char at offset
		// 	break;
		// case 89:
		// 	pokes(); // change short at offset
		// 	break;
		// case 90:
		// 	pokei(); // change int at offset
		// 	break;
		// case 91:
		// 	pokef(); // change float at offset
		// 	break;
		// case 94:
		// 	swp(); // swap top 2 stack elements
		// 	break;
		// case 100:
		// 	add(); // add top 2 stack elements
		// 	break;
		// case 104:
		// 	sub(); // subtract top 2 stack elements
		// 	break;
		// case 108:
		// 	mul(); // multiply top 2
		// 	break;
		// case 112:
		// 	div(); // divide top 2
		// 	break;
		// case 148:
		// 	printc(); // print char
		// 	break;
		// case 149:
		// 	prints(); // print short
		// 	break;
		// case 150:
		// 	printi(); // print int
		// 	break;
		// case 151:
		// 	printf(); // print float
		// 	break;
		// case 0:
		// 	halt(); // terminate the program
		// 	break;

	}
	return 1;
}

void Bytecode::pushi(Datatype::Type t, int index)
{
	int data = converttoInt(mem, index);
	cout << "converted to: " << data << endl;
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
}

void Bytecode::printstack() {
	/*for (vector<Datatype>::const_iterator it = rstack.begin(); it != rstack.end(); ++it) {
		cout << it->int_value << endl;
	}*/
	for (int i = 0; i < rstack.size(); i++) {
		Datatype d = *rstack[i];
		cout << d.int_value << endl;
	}
}