#include "RamMemory.hpp"
#include<exception>
#include<string>
#include<iostream>
RamMemory::RamMemory(int ram)
{
	memory.resize(ram, 0);
	std::cout << memory.size();
}

char RamMemory::read(int index)
{
	return memory[index];
}

void RamMemory::write(int index, char value)
{
	memory[index] = value;
}

int RamMemory::getSize() const
{
	return memory.size();
}
