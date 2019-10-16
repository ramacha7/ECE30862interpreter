#include "Type.h"

class BytecodeChar{
public:
	BytecodeChar();
	virtual ~BytecodeChar();
	BytecodeChar(Type type, char value);
	char converttoChar(char * arr, int pc);
}