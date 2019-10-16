#include "Type.h"

class BytecodeFloat{
public:
	BytecodeFloat();
	virtual ~BytecodeFloat();
	BytecodeFloat(Type type, float value);
	float converttoFloat(char * arr, int pc);
}