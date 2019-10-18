#include "Type.h"
#include "Datatype.h"

class BytecodeChar : public Datatype{
public:
	BytecodeChar();
	virtual ~BytecodeChar();
	BytecodeChar(Type type, char value);
	char converttoChar(char * arr, int pc);
};