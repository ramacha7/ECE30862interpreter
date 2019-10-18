#include "Type.h"
#include "Datatype.h"

class BytecodeInt : public Datatype{
public:
	BytecodeInt();
	virtual ~BytecodeInt();
	BytecodeInt(Type type, int value);
	int converttoInt(char * arr, int pc);
};