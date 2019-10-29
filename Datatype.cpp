#include "Datatype.h"

Datatype::Datatype(){
	type = Int;
	int_value = -1;
	float_value = -1;
	short_value = -1;
	char_value = -1;
}

Datatype::~Datatype(){}

Datatype::Datatype(Type t, int int_val) {
	type = t;
	int_value = int_val;
	float_value = -1;
	short_value = -1;
	char_value = -1;
}
Datatype::Datatype(Type t, float float_val) {
	type = t;
	int_value = -1;
	float_value = float_val;
	short_value = -1;
	char_value = -1;
}
Datatype::Datatype(Type t, short short_val) {
	type = t;
	int_value = -1;
	float_value = -1;
	short_value = short_val;
	char_value = -1;
}
Datatype::Datatype(Type t, char char_val) {
	type = t;
	int_value = -1;
	float_value = -1;
	short_value = -1;
	char_value = char_val;
}

Datatype::Type Datatype::getType() {
	return this->type;
}