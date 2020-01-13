#pragma once
#include<vector>

class RamMemory
{
	std::vector<char> memory;
	
public:
	RamMemory(int ram = 255);

	char read(int index);
	void write(int index, char value);

	int getSize() const;
};

