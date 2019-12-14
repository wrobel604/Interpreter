#pragma once
#include<vector>

#define getAX() readFromMemory(0)
#define getBX() readFromMemory(1)
#define getCX() readFromMemory(2)
#define getDX() readFromMemory(3)

#define setAX(value) writeInMemory(0, value)
#define setBX(value) writeInMemory(1, value)
#define setCX(value) writeInMemory(2, value)
#define setDX(value) writeInMemory(3, value)

class RamInterface {
protected:
	std::vector<char> memory;
public:
	RamInterface(int size);

	int getMemorySize() const;
	char readFromMemory(int position) const;
	void writeInMemory(int position, char value);
};