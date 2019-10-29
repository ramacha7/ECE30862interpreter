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

void Bytecode::interpreter(int size){
	int i = 0;
	int offset = 0;
	while(i < size)
	{
		int code = (int)mem[i];
		offset = byteSwitch(code,i);

		i += offset;
		pc += offset;	
		printstack(); // delete later
	}
}

void Bytecode::printstack() { // delete later
	for (int i = 0; i < rstack.size(); i++) {
		Datatype d = *rstack[i];
		cout << d.int_value << endl;
	}
}

int Bytecode::convertToInt(vector<unsigned char> arr, int pc)
{
	int i = (int)(arr[pc + 1] ^ (arr[pc + 2] << 8) ^ (arr[pc + 3] << 16) ^ (arr[pc + 4] << 24));
	return i;
}

float Bytecode::convertToFloat(vector<unsigned char> arr, int pc){
	float f = (float)(arr[pc + 1] ^ (arr[pc + 2] << 8) ^ (arr[pc + 3] << 16) ^ (arr[pc + 4] << 24));
	return f;
}

short Bytecode::convertToShort(vector<unsigned char> arr, int pc){
	short s = (int)(arr[pc + 1] ^ (arr[pc + 2] << 8));
	return s;
}

char Bytecode::convertToChar(vector<unsigned char> arr, int pc){
	char c = (char)(arr[pc + 1]);
	return c;
}

int Bytecode::byteSwitch(int code,int index){
	switch(code){
		 case 132:
		 	// convert
		 	// make object
		 	cmpe(index); // compare (equal)
		 	break;
		 case 136:
		 	cmplt(index); // compare (less than)
		 	break;
		 case 140:
		 	cmpgt(index); // compare (greater than)
		 	break;
		 case 36:
		 	jmp(index); // jump to location of runtime stack
		 	break;
		 case 40:
		 	jmpc(index); // jump if next on rstack is 1
		 	break;
		 case 44:
		 	call(index); // same fpstack and jump
		 	break;
		 case 48:
		 	ret(index); // restore rstack pointer 
		 	break;
		 case 68:
		 	pushc(index); // push char
		 	break;
		 case 69:
		 	pushs(index); // push short
		 	break;
		case 70:
			pushi(index); // push int
			return 5;
			break;
		 case 71:
		 	pushf(index); // push float
		 	break;
		 case 72:
		 	pushvc(index); // push variable char
		 	break;
		 case 73:
		 	pushvs(index); // push variable short
		 	break;
		 case 74:
		 	pushvi(index); // push variable int
		 	break;
		 case 75:
		 	pushvf(index); // push variable float
		 	break;
		 case 76:
		 	popm(index); // pop multiple values
		 	break;
		 case 80:
		 	popv(index); // pop value into variable
		 	break;
		 case 77:
		 	popa(index); // pop all top entries 
		 	break;
		 case 84:
		 	peekc(index); // take char value at offset
		 	break;
		 case 85:
		 	peeks(index); // take short value at offset
		 	break;
		 case 86:
		 	peeki(index); // take int value at offset
		 	break;
		 case 87:
		 	peekf(index); // take float value at offset
		 	break;
		 case 88:
		 	pokec(index); // change char at offset
		 	break;
		 case 89:
		 	pokes(index); // change short at offset
		 	break;
		 case 90:
		 	pokei(index); // change int at offset
		 	break;
		 case 91:
		 	pokef(index); // change float at offset
		 	break;
		 case 94:
		 	swp(index); // swap top 2 stack elements
		 	break;
		 case 100:
		 	add(index); // add top 2 stack elements
		 	break;
		 case 104:
		 	sub(index); // subtract top 2 stack elements
		 	break;
		 case 108:
		 	mul(index); // multiply top 2
		 	break;
		 case 112:
		 	div(index); // divide top 2
		 	break;
		 case 148:
		 	printc(index); // print char
		 	break;
		 case 149:
		 	prints(index); // print short
		 	break;
		 case 150:
		 	printi(index); // print int
		 	break;
		 case 151:
		 	printf(index); // print float
		 	break;
		 case 0:
		 	halt(index); // terminate the program
		 	break;
	}
}

void Bytecode::cmpe(int index) {}
void Bytecode::cmplt(int index) {}
void Bytecode::cmpgt(int index) {}
void Bytecode::jmp(int index) {}
void Bytecode::jmpc(int index) {}
void Bytecode::call(int index) {}
void Bytecode::ret(int index) {}

void Bytecode::pushc(int index) {
	Datatype::Type t = Datatype::Char;
	char data = convertToChar(mem, index);
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
}

void Bytecode::pushs(int index) {
	Datatype::Type t = Datatype::Short;
	short data = convertToShort(mem, index);
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
}

void Bytecode::pushi(int index){
	Datatype::Type t = Datatype::Int;
	int data = convertToInt(mem, index);
	//cout << "converted to: " << data << endl;
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
}

void Bytecode::pushf(int index) {
	Datatype::Type t = Datatype::Float;
	float data = convertToFloat(mem, index);
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
}

void Bytecode::pushvc(int index){}
void Bytecode::pushvs(int index){}
void Bytecode::pushvi(int index){}
void Bytecode::pushvf(int index){}
void Bytecode::popm(int index){}
void Bytecode::popv(int index){}
void Bytecode::popa(int index){}
void Bytecode::peekc(int index){}
void Bytecode::peeks(int index){}
void Bytecode::peeki(int index){}
void Bytecode::peekf(int index){}
void Bytecode::pokec(int index){}
void Bytecode::pokes(int index){}
void Bytecode::pokei(int index){}
void Bytecode::pokef(int index){}
void Bytecode::swp(int index){}
void Bytecode::add(int index){}
void Bytecode::sub(int index){}
void Bytecode::mul(int index){}
void Bytecode::div(int index){}
void Bytecode::printc(int index){}
void Bytecode::prints(int index){}
void Bytecode::printi(int index){}
void Bytecode::printf(int index){}
void Bytecode::halt(int index){}


