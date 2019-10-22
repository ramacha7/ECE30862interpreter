#include "BytecodeInt.h"

BytecodeInt::BytecodeInt(){}
BytecodeInt::~BytecodeInt(){}
BytecodeInt::BytecodeInt(Type typ, int val){
	type = typ;
	value = value;
}

int BytecodeInt::converttoInt(vector<unsigned char> arr, int pc)
{
	int i = (int)(arr[pc+1] ^ (arr[pc+2] << 8) ^ (arr[pc+3] << 16) ^ (arr[pc+4] << 24));
	return i;
}