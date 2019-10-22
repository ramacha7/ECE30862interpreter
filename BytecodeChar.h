#ifndef _bytecodechar_h_
#define _bytecodechar_h_

//#include "Type.h"
#include "Datatype.h"
#include "Bytecode.h"

class BytecodeChar : public Datatype{
public:
	Type type;
	char value;
	BytecodeChar();
	virtual ~BytecodeChar();
	BytecodeChar(Type typ, char val);
	char converttoChar(char * arr, int pc);
};

#endif