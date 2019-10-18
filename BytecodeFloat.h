#include "Type.h"
#include "Datatype.h"

class BytecodeFloat : public Datatype{
public:
	BytecodeFloat();
	virtual ~BytecodeFloat();
	BytecodeFloat(Type type, float value);
	float converttoFloat(char * arr, int pc);
};