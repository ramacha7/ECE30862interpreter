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
	size = 27;
	while(pc < size)
	{
		int code = (int)mem[pc];
		byteSwitch(code);
		printstack(); // delete later
	}
}

void Bytecode::printstack() { // delete later
	//cout<<"The current stack is: ";
	//for (int i = 0; i < rstack.size(); i++) {
	//	Datatype::Type t = rstack[i]->type;
	//	Datatype d = *rstack[i];
	//	if (t == Datatype::Char) {
	//		cout << d.char_value << " ";
	//	}
	//	else if (t == Datatype::Short) {
	//		cout << d.short_value << " ";
	//	}
	//	else if (t == Datatype::Int) {
	//		cout << d.int_value << " ";
	//	}
	//	else {
	//		cout << d.float_value << " ";
	//	}
	//}
	//cout <<endl;
	cout << "pc: " << pc << endl;
	cout << "sp: " << sp << endl;
	cout << "rstack: ";
	if (rstack.size() == 0) {
		cout << "empty" << endl;
	}
	else {
		for (int i = 0; i < rstack.size(); i++) {
			Datatype::Type t = rstack[i]->type;
			if (t == Datatype::Char) {
				cout << rstack[i]->char_value << " ";
			}
			else if (t == Datatype::Short) {
				cout << rstack[i]->short_value << " ";
			}
			else if (t == Datatype::Int) {
				cout << rstack[i]->int_value << " ";
			}
			else {
				cout << rstack[i]->float_value << " ";
			}
		}
		cout << endl;
	}
	cout << "fpsp: " << fpsp << endl;
	cout << "fpstack: ";
	if (fpstack.size() == 0) {
		cout << "empty" << endl;
	}
	else {
		for (int j = 0; j < fpstack.size(); j++) {
			cout << fpstack[j] << " ";
		}
		cout << endl;
	}
}

int Bytecode::convertToInt()
{
	int i = (int)(mem[pc + 1] ^ (mem[pc + 2] << 8) ^ (mem[pc + 3] << 16) ^ (mem[pc + 4] << 24));
	return i;
}

float Bytecode::convertToFloat() {
	float f = (float)(mem[pc + 1] ^ (mem[pc + 2] << 8) ^ (mem[pc + 3] << 16) ^ (mem[pc + 4] << 24));
	return f;
}

short Bytecode::convertToShort() {
	short s = (int)(mem[pc + 1] ^ (mem[pc + 2] << 8));
	return s;
}

char Bytecode::convertToChar() {
	char c = (char)(mem[pc + 1]);
	return c;
}

//int Bytecode::byteSwitch(int code,int index){
void Bytecode::byteSwitch(int code) {
	switch(code){
		 case 132:
		 	// convert
		 	// make object
		 	cmpe(); // compare (equal)
		 	break;
		 case 136:
		 	cmplt(); // compare (less than)
		 	break;
		 case 140:
		 	cmpgt(); // compare (greater than)
		 	break;
		 case 36:
		 	jmp(); // jump to location of runtime stack
		 	break;
		 case 40:
		 	jmpc(); // jump if next on rstack is 1
		 	break;
		 case 44:
		 	call(); // same fpstack and jump
		 	break;
		 case 48:
		 	ret(); // restore rstack pointer 
		 	break;
		 case 68:
		 	pushc(); // push char
		 	break;
		 case 69:
		 	pushs(); // push short
		 	break;
		case 70:
			pushi(); // push int
			break;
		 case 71:
		 	pushf(); // push float
		 	break;
		 case 72:
		 	pushvc(); // push variable char
		 	break;
		 case 73:
		 	pushvs(); // push variable short
		 	break;
		 case 74:
		 	pushvi(); // push variable int
		 	break;
		 case 75:
		 	pushvf(); // push variable float
		 	break;
		 case 76:
		 	popm(); // pop multiple values
		 	break;
		 case 80:
		 	popv(); // pop value into variable
		 	break;
		 case 77:
		 	popa(); // pop all top entries
		 	break;
		 case 84:
		 	peekc(); // take char value at offset
		 	break;
		 case 85:
		 	peeks(); // take short value at offset
		 	break;
		 case 86:
		 	peeki(); // take int value at offset
		 	break;
		 case 87:
		 	peekf(); // take float value at offset
		 	break;
		 case 88:
		 	pokec(); // change char at offset
		 	break;
		 case 89:
		 	pokes(); // change short at offset
		 	break;
		 case 90:
		 	pokei(); // change int at offset
		 	break;
		 case 91:
		 	pokef(); // change float at offset
		 	break;
		 case 94:
		 	swp(); // swap top 2 stack elements
		 	break;
		 case 100:
		 	add(); // add top 2 stack elements
		 	break;
		 case 104:
		 	sub(); // subtract top 2 stack elements
		 	break;
		 case 108:
		 	mul(); // multiply top 2
		 	break;
		 case 112:
		 	div(); // divide top 2
		 	break;
		 case 144:
		 	printc(); // print char
		 	break;
		 case 145:
		 	prints(); // print short
		 	break;
		 case 146:
		 	printi(); // print int
		 	break;
		 case 147:
		 	printf(); // print float
		 	break;
		 case 0:
		 	halt(); // terminate the program
		 	break;
	}
}

void Bytecode::cmpe() {
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
	pc++;
}

void Bytecode::cmplt() {
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
	pc++;
}

void Bytecode::cmpgt( ) {
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
	pc++;
}

void Bytecode::jmp( ) {
	pc = rstack[sp]->int_value;
	sp--;
	rstack.pop_back();
}

void Bytecode::jmpc( ) {
	if (rstack[sp - 1]->int_value) {
		pc = rstack[sp]->int_value;
		sp -= 2;
		rstack.pop_back();
		rstack.pop_back();
	}
	pc++;
}
void Bytecode::call( ) {
	fpstack[++fpsp] = sp - rstack[sp]->int_value - 1;
	sp--;
	pc = rstack[sp--]->int_value;
	rstack.pop_back();
	rstack.pop_back();
}

void Bytecode::ret( ) {
	sp = fpstack[fpsp--];
	pc = rstack[sp--]->int_value;
	fpstack.pop_back();
	rstack.pop_back();
}

void Bytecode::pushc( ) {
	Datatype::Type t = Datatype::Char;
	char data = convertToChar();
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 2;
}

void Bytecode::pushs( ) {
	Datatype::Type t = Datatype::Short;
	short data = convertToShort();
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 3;
}

void Bytecode::pushi( ){
	Datatype::Type t = Datatype::Int;
	int data = convertToInt();
	//cout << "converted to: " << data << endl;
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 5;
}

void Bytecode::pushf( ) {
	Datatype::Type t = Datatype::Float;
	float data = convertToFloat();
	Datatype* d = new Datatype(t, data);
	rstack.push_back(d);
	++sp;
	pc += 5;
}


// Check with TAs about whether the top most element on runtime stack will always be of int type
void Bytecode::pushvc( ){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->char_value = rstack[fpstack[fpsp] + offsetindex + 1]->char_value;
	rstack[sp]->type = Datatype::Char;
	pc++;
}
void Bytecode::pushvs( ){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->short_value = rstack[fpstack[fpsp] + offsetindex + 1]->short_value;
	rstack[sp]->type = Datatype::Short;
	pc++;
}
void Bytecode::pushvi( ){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->int_value = rstack[fpstack[fpsp] + offsetindex + 1]->int_value;
	rstack[sp]->type = Datatype::Int;
	pc++;
}
void Bytecode::pushvf( ){
	int offsetindex = rstack[sp]->int_value;
	rstack[sp]->float_value = rstack[fpstack[fpsp] + offsetindex + 1]->float_value;
	rstack[sp]->type = Datatype::Float;
	pc++;
}

void Bytecode::popm( ){
	int i = 0;
	int n = rstack[sp]->int_value + 1;
	while(i < n)
	{
		rstack.pop_back();
		sp -= 1;
	}
	pc++;
}
void Bytecode::popv( ){
	Datatype *d1 = rstack[sp - 1];
	Datatype::Type t = d1->getType();
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
	pc++;
}

void Bytecode::popa( ){
	int num = rstack[sp]->int_value;
	int location = fpstack[fpsp];
	location += 1;
	for (int i = 0; i < num; i++) {
		Datatype::Type t = rstack[sp - num + i]->type;
		if (t == Datatype::Char) {
			rstack[location + i]->type = t;
			rstack[location + i]->char_value = rstack[sp - num + i]->char_value;
		}
		if (t == Datatype::Short) {
			rstack[location + i]->type = t;
			rstack[location + i]->short_value = rstack[sp - num + i]->short_value;
		}
		if (t == Datatype::Int) {
			rstack[location + i]->type = t;
			rstack[location + i]->int_value = rstack[sp - num + i]->int_value;
		}
		if (t == Datatype::Float) {
			rstack[location + i]->type = t;
			rstack[location + i]->float_value = rstack[sp - num + i]->float_value;
		}
	}
	while (sp >= location + num) {
		sp--;
		rstack.pop_back();
	}
}

void Bytecode::peekc( ){
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->char_value = rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->char_value;
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->type = Datatype::Char;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}

void Bytecode::peeks( ){
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->short_value = rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->short_value;
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->type = Datatype::Short;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}
void Bytecode::peeki( ){
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->int_value = rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->int_value;
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->type = Datatype::Int;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}
void Bytecode::peekf( ){
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->float_value = rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->float_value;
	rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->type = Datatype::Float;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}
void Bytecode::pokec( ){
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->char_value = rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->char_value;
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->type = Datatype::Char;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}
void Bytecode::pokes( ){
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->short_value = rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->short_value;
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->type = Datatype::Short;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}
void Bytecode::pokei( ){
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->int_value = rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->int_value;
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->type = Datatype::Int;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}
void Bytecode::pokef( ){
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->float_value = rstack[fpstack[fpsp] + rstack[sp - 1]->int_value + 1]->float_value;
	rstack[fpstack[fpsp] + rstack[sp]->int_value + 1]->type = Datatype::Float;
	pc++;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
}

// change this later
void Bytecode::swp(){
	Datatype* tmp = rstack[sp - 1];
	rstack[sp - 1] = rstack[sp];
	rstack[sp] = tmp;
	pc++;
	if (fpstack[fpsp] = sp) {
		fpstack[fpsp] = sp - 1;
	}
	else if (fpstack[fpsp] = sp - 1) {
		fpstack[fpsp] = sp;
	}
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
	pc++;
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
	pc++;
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
	pc++;
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
	pc++;
}

void Bytecode::printc(){
	Datatype *d = rstack[sp];
	char c = d->char_value;
	cout << c << endl;
	rstack.pop_back();
	--sp;
	pc++;
}

void Bytecode::prints(){
	Datatype* d = rstack[sp];
	short s = d->short_value;
	cout << s << endl;
	rstack.pop_back();
	--sp;
	pc++;
}

void Bytecode::printi(){
	Datatype* d = rstack[sp];
	int i = d->int_value;
	cout << "The top value is :" << i << endl;
	rstack.pop_back();
	--sp;
	pc++;
}

void Bytecode::printf(){
	Datatype* d = rstack[sp];
	float f = d->float_value;
	cout << f << endl;
	rstack.pop_back();
	--sp;
	pc++;
}


void Bytecode::halt( ){
	cout << "pc: " << pc << endl;
	cout << "sp: " << sp << endl;
	cout << "rstack: ";
	if (rstack.size() == 0) {
		cout << "empty" << endl;
	}
	else {
		for (int i = 0; i < rstack.size(); i++) {
			Datatype::Type t = rstack[i]->type;
			if (t == Datatype::Char) {
				cout << rstack[i]->char_value << " ";
			}
			else if (t == Datatype::Short) {
				cout << rstack[i]->short_value << " ";
			}
			else if (t == Datatype::Int) {
				cout << rstack[i]->int_value << " ";
			}
			else {
				cout << rstack[i]->float_value << " ";
			}
		}
		cout << endl;
	}
	cout << "fpsp: " << fpsp << endl;
	cout << "fpstack: ";
	if (fpstack.size() == 0) {
		cout << "empty" << endl;
	}
	else {
		for (int j = 0; j < fpstack.size(); j++) {
			cout << fpstack[j] << " ";
		}
		cout << endl;
	}
	pc = mem.size();
}


