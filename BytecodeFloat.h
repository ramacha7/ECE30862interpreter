#include "Type.h"
#include "Bytecode.h"

class BytecodeFloat : public Bytecode{
public:
	BytecodeFloat();
	virtual ~BytecodeFloat();
	BytecodeFloat(Type type, float value);
}