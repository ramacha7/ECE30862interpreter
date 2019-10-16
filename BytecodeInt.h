#include "Type.h"

class BytecodeInt{
public:
	BytecodeInt();
	virtual ~BytecodeInt();
	BytecodeInt(Type type, int value);
	int converttoInt(char * arr, int pc);
}