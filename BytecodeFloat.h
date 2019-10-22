#ifndef _bytecodefloat_h_
#define _bytecodefloat_h_

//#include "Type.h"
#include "Datatype.h"
#include "Bytecode.h"

class BytecodeFloat : public Datatype{
public:
	Type type;
	float value;
	BytecodeFloat();
	virtual ~BytecodeFloat();
	BytecodeFloat(Type typ, float val);
	float converttoFloat(char * arr, int pc);
};

#endif