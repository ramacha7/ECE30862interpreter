#include "Type.h"
#include "Datatype.h"

class BytecodeShort : public Datatype{
public:
	BytecodeShort();
	virtual ~BytecodeShort();
	BytecodeShort(Type type, short value);
	short converttoShort(char * arr, int pc);
};