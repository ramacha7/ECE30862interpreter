#include "Type.h"
#include "Bytecode.h"

class BytecodeChar : public Bytecode{
public:
	BytecodeChar();
	virtual ~BytecodeChar();
	BytecodeChar(Type type, char value);
}