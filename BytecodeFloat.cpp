#include "BytecodeFloat.h"

BytecodeFloat::BytecodeFloat(){}
BytecodeFloat::~BytecodeFloat(){}
BytecodeFloat::BytecodeFloat(Type type, float value){
	Type type = type;
	float value = value;
}

float BytecodeFloat::converttoFloat(char * arr, int pc)
{
	float f = (float)(arr[pc+1] ^ (arr[pc+2] << 8) ^ (arr[pc+3] << 16) ^ (arr[pc+4] << 24));
	return f;
}