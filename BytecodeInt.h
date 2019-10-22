#include "Type.h"
#include "Datatype.h"
#include <vector>

using namespace std;

class BytecodeInt : public Datatype{
public:

	int value;
	Type type;

	BytecodeInt();
	virtual ~BytecodeInt();
	BytecodeInt(Type type, int value);
	int converttoInt(vector<unsigned char> arr, int pc);
};