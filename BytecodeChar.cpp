#include "BytecodeChar.h"

BytecodeChar::BytecodeChar(){}
BytecodeChar::~BytecodeChar(){}
BytecodeChar::BytecodeChar(Type typ, char val){
	type = typ;
	value = val;
}
char BytecodeChar::converttoChar(char * arr, int pc)
{
	char c = (char)(arr[pc+1]);
	return c;
}