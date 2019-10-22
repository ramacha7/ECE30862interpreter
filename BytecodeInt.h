#ifndef _bytecodeint_h_
#define _bytecodeint_h_

//#include "Type.h"
#include "Datatype.h"
#include <vector>
//#include "Bytecode.h"

using namespace std;

class BytecodeInt : public Datatype{
public:

	int value;
	Type type;

	BytecodeInt();
	virtual ~BytecodeInt();
	BytecodeInt(Type typ, int val);
};

#endif