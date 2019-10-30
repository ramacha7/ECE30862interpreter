#include "Bytecode.h"
#include "Datatype.h"
#include <iostream>
#include <vector>

using namespace std;

Bytecode::Bytecode(){
	sp = -1;
	fpsp = -1;
	pc = 0;
	mem.reserve(0);
}

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
		printstack(); // delete later
	}
}

void Bytecode::printstack() { // delete later
	cout<<"The current stack is:"<<endl;
	for (int i = 0; i < rstack.size(); i++) {
		Datatype d = *rstack[i];
		cout << d.int_value << " ";
	}
	cout <<endl;
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
			return 1;
		 	break;
		 case 136:
		 	cmplt(index); // compare (less than)
			return 1;
		 	break;
		 case 140:
		 	cmpgt(index); // compare (greater than)
			return 1;
		 	break;
		 case 36:
		 	jmp(index); // jump to location of runtime stack
			return 1;
		 	break;
		 case 40:
		 	jmpc(index); // jump if next on rstack is 1
			return 1;
		 	break;
		 case 44:
		 	call(index); // same fpstack and jump
			return 1;
		 	break;
		 case 48:
		 	ret(index); // restore rstack pointer 
			return 1;
		 	break;
		 case 68:
		 	pushc(index); // push char
			return 2;
		 	break;
		 case 69:
		 	pushs(index); // push short
			return 3;
		 	break;
		case 70:
			pushi(index); // push int
			return 5;
			break;
		 case 71:
		 	pushf(index); // push float
			return 5;
		 	break;
		 case 72:
		 	pushvc(index); // push variable char
			return 1;
		 	break;
		 case 73:
		 	pushvs(index); // push variable short
			return 1;
		 	break;
		 case 74:
		 	pushvi(index); // push variable int
			return 1;
		 	break;
		 case 75:
		 	pushvf(index); // push variable float
			return 1;
		 	break;
		 case 76:
		 	popm(index); // pop multiple values
			return 1;
		 	break;
		 case 80:
		 	popv(index); // pop value into variable
			return 1;
		 	break;
		 case 77:
		 	popa(index); // pop all top entries
			return 1; 
		 	break;
		 case 84:
		 	peekc(index); // take char value at offset
			return 1;
		 	break;
		 case 85:
		 	peeks(index); // take short value at offset
			return 1;
		 	break;
		 case 86:
		 	peeki(index); // take int value at offset
			return 1;
		 	break;
		 case 87:
		 	peekf(index); // take float value at offset
			return 1;
		 	break;
		 case 88:
		 	pokec(index); // change char at offset
			return 1;
		 	break;
		 case 89:
		 	pokes(index); // change short at offset
			return 1;
		 	break;
		 case 90:
		 	pokei(index); // change int at offset
			return 1;
		 	break;
		 case 91:
		 	pokef(index); // change float at offset
			return 1;
		 	break;
		 case 94:
		 	swp(); // swap top 2 stack elements
			return 1;
		 	break;
		 case 100:
		 	add(); // add top 2 stack elements
			return 1;
		 	break;
		 case 104:
		 	sub(); // subtract top 2 stack elements
			return 1;
		 	break;
		 case 108:
		 	mul(); // multiply top 2
			return 1;
		 	break;
		 case 112:
		 	div(); // divide top 2
			return 1;
		 	break;
		 case 144:
		 	printc(); // print char
			return 1;
		 	break;
		 case 145:
		 	prints(); // print short
			return 1;
		 	break;
		 case 146:
		 	printi(); // print int
			return 1;
		 	break;
		 case 147:
		 	printf(); // print float
			return 1;
		 	break;
		 case 0:
		 	halt(index); // terminate the program
			return 1;
		 	break;
	}
}

void Bytecode::cmpe(int index) {
	Datatype *d1 = rstack[sp-1];
	Datatype *d2 = rstack[sp];
	Datatype::Type t = d1->getType();
	if (t == Datatype::Int) {
		d1->int_value = d1->int_value == d2->int_value;
	}
	else if (t == Datatype::Char) {
		d1->char_value = d1->char_value == d2->char_value;
	}
	else if (t == Datatype::Short) {
		d1->short_value = d1->short_value == d2->short_value;
	}
	else {
		d1->float_value = d1->float_value == d2->float_value;
	}
	sp--;
	rstack.pop_back();
}

void Bytecode::cmplt(int index) {
	Datatype *d1 = rstack[sp-1];
	Datatype *d2 = rstack[sp];
	Datatype::Type t = d1->getType();
	if (t == Datatype::Int) {
		d1->int_value = d1->int_value < d2->int_value;
	}
	else if (t == Datatype::Char) {
		d1->char_value = d1->char_value < d2->char_value;
	}
	else if (t == Datatype::Short) {
		d1->short_value = d1->short_value < d2->short_value;
	}
	else {
		d1->float_value = d1->float_value < d2->float_value;
	}
	sp--;
	rstack.pop_back();
}

void Bytecode::cmpgt(int index) {
	Datatype *d1 = rstack[sp-1];
	Datatype *d2 = rstack[sp];
	Datatype::Type t = d1->getType();
	if (t == Datatype::Int) {
		d1->int_value = d1->int_value > d2->int_value;
	}
	else if (t == Datatype::Char) {
		d1->char_value = d1->char_value > d2->char_value;
	}
	else if (t == Datatype::Short) {
		d1->short_value = d1->short_value > d2->short_value;
	}
	else {
		d1->float_value = d1->float_value > d2->float_value;
	}
	sp--;
	rstack.pop_back();
}

void Bytecode::jmp(int index) {}
void Bytecode::jmpc(int index) {}
void Bytecode::call(int index) {}
void Bytecode::ret(int index) {}

void Bytecode::pushc(int index) {
	Datatype::Type t = Datatype::Char;
	char data = convertToChar(mem, index);
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 2;
}

void Bytecode::pushs(int index) {
	Datatype::Type t = Datatype::Short;
	short data = convertToShort(mem, index);
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 3;
}

void Bytecode::pushi(int index){
	Datatype::Type t = Datatype::Int;
	int data = convertToInt(mem, index);
	//cout << "converted to: " << data << endl;
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 5;
}

void Bytecode::pushf(int index) {
	Datatype::Type t = Datatype::Float;
	float data = convertToFloat(mem, index);
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 5;
}


// Check with TAs about whether the top most element on runtime stack will always be of int type
void Bytecode::pushvc(int index){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->char_value = rstack[fpstack[fpsp] + offsetindex + 1];
	rstack[sp]->type = Datatype::Char;
}
void Bytecode::pushvs(int index){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->short_value = rstack[fpstack[fpsp] + offsetindex + 1];
	rstack[sp]->type = Datatype::Short;
}
void Bytecode::pushvi(int index){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->int_value = rstack[fpstack[fpsp] + offsetindex + 1];
	rstack[sp]->type = Datatype::Int;
}
void Bytecode::pushvf(int index){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->float_value = rstack[fpstack[fpsp] + offsetindex + 1];
	rstack[sp]->type = Datatype::Float;
}

void Bytecode::popm(int index){
	int i = 0;
	int n = rstack[sp]->int_value + 1;
	while(i < n)
	{
		rstack.pop_back();
		sp -= 1;
	}
}
void Bytecode::popv(int index){
	if (t == Datatype::Int) {
		rstack[fpstack[fpsp]+(rstack[sp]->int_value)+1]->int_value = rstack[sp-1]->int_value;
	}
	else if (t == Datatype::Char) {
		rstack[fpstack[fpsp]+(rstack[sp]->int_value)+1]->char_value = rstack[sp-1]->char_value;
	}
	else if (t == Datatype::Short) {
		rstack[fpstack[fpsp]+(rstack[sp]->int_value)+1]->short_value = rstack[sp-1]->short_value;
	}
	else {
		rstack[fpstack[fpsp]+(rstack[sp]->int_value)+1]->float_value = rstack[sp-1]->float_value;
	}
	
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;

}
void Bytecode::popa(int index){}
void Bytecode::peekc(int index){}
void Bytecode::peeks(int index){}
void Bytecode::peeki(int index){}
void Bytecode::peekf(int index){}
void Bytecode::pokec(int index){}
void Bytecode::pokes(int index){}
void Bytecode::pokei(int index){}
void Bytecode::pokef(int index){}

void Bytecode::swp(){
	Datatype* tmp = rstack[sp - 1];
	rstack[sp - 1] = rstack[sp];
	rstack[sp] = tmp;
}

void Bytecode::add(){
	Datatype *d1 = rstack[sp - 1];
	Datatype *d2 = rstack[sp];
	Datatype::Type t = d1->getType();
	if (t == Datatype::Int) {
		d1->int_value = d1->int_value + d2->int_value;
	}
	else if (t == Datatype::Char) {
		d1->char_value = d1->char_value + d2->char_value;
	}
	else if (t == Datatype::Short) {
		d1->short_value = d1->short_value + d2->short_value;
	}
	else {
		d1->float_value = d1->float_value + d2->float_value;
	}
	rstack.pop_back();
	sp--;
}

void Bytecode::sub(){
	Datatype* d1 = rstack[sp - 1];
	Datatype* d2 = rstack[sp];
	Datatype::Type t = d1->getType();
	if (t == Datatype::Int) {
		d1->int_value = d1->int_value - d2->int_value;
	}
	else if (t == Datatype::Char) {
		d1->char_value = d1->char_value - d2->char_value;
	}
	else if (t == Datatype::Short) {
		d1->short_value = d1->short_value - d2->short_value;
	}
	else {
		d1->float_value = d1->float_value - d2->float_value;
	}
	rstack.pop_back();
	sp--;
}

void Bytecode::mul(){
	Datatype* d1 = rstack[sp - 1];
	Datatype* d2 = rstack[sp];
	Datatype::Type t = d1->getType();
	if (t == Datatype::Int) {
		d1->int_value = d1->int_value * d2->int_value;
	}
	else if (t == Datatype::Char) {
		d1->char_value = d1->char_value * d2->char_value;
	}
	else if (t == Datatype::Short) {
		d1->short_value = d1->short_value * d2->short_value;
	}
	else {
		d1->float_value = d1->float_value * d2->float_value;
	}
	sp--;
	rstack.pop_back();
}

void Bytecode::div(){
	Datatype* d1 = rstack[sp - 1];
	Datatype* d2 = rstack[sp];
	Datatype::Type t = d1->getType();
	if (t == Datatype::Int) {
		d1->int_value = d1->int_value / d2->int_value;
	}
	else if (t == Datatype::Char) {
		d1->char_value = d1->char_value / d2->char_value;
	}
	else if (t == Datatype::Short) {
		d1->short_value = d1->short_value / d2->short_value;
	}
	else {
		d1->float_value = d1->float_value / d2->float_value;
	}
	rstack.pop_back();
	sp--;
}

void Bytecode::printc(){
	Datatype *d = rstack[sp];
	char c = d->char_value;
	cout << c << endl;
	rstack.pop_back();
	--sp;
}

void Bytecode::prints(){
	Datatype* d = rstack[sp];
	short s = d->short_value;
	cout << s << endl;
	rstack.pop_back();
	--sp;
}

void Bytecode::printi(){
	Datatype* d = rstack[sp];
	int i = d->int_value;
	cout << "The top value is :" << i << endl;
	rstack.pop_back();
	--sp;
}

void Bytecode::printf(){
	Datatype* d = rstack[sp];
	float f = d->float_value;
	cout << f << endl;
	rstack.pop_back();
	--sp;
}


void Bytecode::halt(int index){}


