#pragma once
#include<vector>

#define getAX() readFromMemory(0)
#define getBX() readFromMemory(1)
#define getCX() readFromMemory(2)
#define getDX() readFromMemory(3)

#define setAX(value) writeToMemory(0, value)
#define setBX(value) writeToMemory(1, value)
#define setCX(value) writeToMemory(2, value)
#define setDX(value) writeToMemory(3, value)

class RamInterface {
protected:
	std::vector<char> memory;
public:
	RamInterface(int size);

	int getMemorySize() const;
	char readFromMemory(int position) const;
	void writeToMemory(int position, char value);
};