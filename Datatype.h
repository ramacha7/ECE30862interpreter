#ifndef _datatype_h_
#define _datatype_h_

#include <vector>
using namespace std;

class Datatype{
    public:
    Datatype();
    virtual ~Datatype();
	enum Type { Char, Short, Int, Float };
};

#endif