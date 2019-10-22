#ifndef _bytecodeshort_h_
#define _bytecodeshort_h_

//#include "Type.h"
#include "Datatype.h"
#include "Bytecode.h"

class BytecodeShort : public Datatype{
public:
	Type type;
	short value;
	BytecodeShort();
	virtual ~BytecodeShort();
	BytecodeShort(Type typ, short val);
	short converttoShort(char * arr, int pc);
};

#endif