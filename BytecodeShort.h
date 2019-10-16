#include "Type.h"

class BytecodeShort{
public:
	BytecodeShort();
	virtual ~BytecodeShort();
	BytecodeShort(Type type, short value);
	short converttoShort(char * arr, int pc);
}