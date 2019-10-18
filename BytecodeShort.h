#include "Type.h"
#include "Bytecode.h"

class BytecodeShort : public Bytecode{
public:
	BytecodeShort();
	virtual ~BytecodeShort();
	BytecodeShort(Type type, short value);
}