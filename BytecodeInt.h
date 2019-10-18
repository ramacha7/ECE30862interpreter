#include "Type.h"
#include "Bytecode.h"

class BytecodeInt : public Bytecode{
public:
	BytecodeInt();
	virtual ~BytecodeInt();
	BytecodeInt(Type type, int value);
}