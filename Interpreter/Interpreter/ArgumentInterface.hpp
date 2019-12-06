#pragma once

class ArgumentInterface {
public:
	virtual char read() const = 0;
	virtual void write(char value) = 0;
};

class ValueArgument : public ArgumentInterface {
	char Value;
public:
	ValueArgument(char value):Value(value){}

	virtual char read() const {
		return Value;
	}
	virtual void write(char value) {
		Value = value;
	}
};

class PointerArgument : public ArgumentInterface {
	char* Value;
public:
	PointerArgument(char* value):Value(value){}

	virtual char read() const {
		return *Value;
	}
	virtual void write(char value) {
		*Value = value;
	}
};