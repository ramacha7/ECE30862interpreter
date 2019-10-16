#include "BytecodeInt.h"

BytecodeInt::BytecodeInt(){}
BytecodeInt::~BytecodeInt(){}
BytecodeInt::BytecodeInt(Type type, int value){
	Type type = type;
	int value = value;
}

int BytecodeFloat::converttoInt(char * arr, int pc)
{
	int i = (int)(arr[pc+1] ^ (arr[pc+2] << 8) ^ (arr[pc+3] << 16) ^ (arr[pc+4] << 24));
	return i;
}