#include"RAM.hpp"

RamInterface::RamInterface(int size)
{
	memory.resize(size, 0);
}

int RamInterface::getMemorySize() const
{
	return memory.size();
}

char RamInterface::readFromMemory(int position) const
{
	return memory[position];
}

void RamInterface::writeToMemory(int position, char value)
{
	memory[position] = value;
}
