#ifndef _datatype_h_
#define _datatype_h_

#include <vector>
using namespace std;

class Datatype{
public:
    Datatype();
    virtual ~Datatype();
	enum Type { Char, Short, Int, Float };
	int int_value;
	float float_value;
	short short_value;
	char char_value;
	Type type;
	Datatype(Type t, int int_val);
	Datatype(Type t, float float_val);
	Datatype(Type t, short short_val);
	Datatype(Type t, char char_val);

	Type getType();
};

#endif