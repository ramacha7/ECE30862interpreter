#include "Type.h"

class BytecodeInt{
public:
	BytecodeInt();
	virtual ~BytecodeInt();
	BytecodeInt(Type type, int value);
}