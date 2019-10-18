#include "BytecodeChar.h"

BytecodeChar::BytecodeChar(){}
BytecodeChar::~BytecodeChar(){}
BytecodeChar::BytecodeChar(Type type, char value){
	Type type = type;
	char value = value;
}
char BytecodeChar::converttoChar(char * arr, int pc)
{
	char c = (char)(arr[pc+1]);
	return c;
}