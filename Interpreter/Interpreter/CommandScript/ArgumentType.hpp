#pragma once

class ArgumentType {
public:
	enum class Type : char {
		Value, 
		Flags,
		Ptr,
		CodePtr,
		AX, BX, CX, DX,
		Unknown
	};
protected:
	Type type;
	char value;
public:
	ArgumentType(Type args_type, char args_value) :type(args_type), value(args_value) {

	}

	Type getType() const { return type; }
	char getValue() const { return value; }
};