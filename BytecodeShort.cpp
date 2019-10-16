#include "BytecodeShort.h"

BytecodeShort::BytecodeShort(){}
BytecodeShort::~BytecodeShort(){}
BytecodeShort::BytecodeShort(Type type, short value){
	Type type = type;
	short value = value;
}

short BytecodeShort::converttoShort(char * arr, int pc)
{
	short s = (int)(arr[pc+1] ^ (arr[pc+2] << 8));
	return s;
}