#include "RamMemory.hpp"
#include<iomanip>
#include<iostream>

RamMemory::RamMemory(int ram)
{
	memory.resize(ram, ' ');
	programSize = 0;
}

int RamMemory::getMemorySize() const
{
	return memory.size();
}

int RamMemory::getProgramSize() const
{
	return programSize;
}

char RamMemory::readFromDataMemory(int adrr)
{
	adrr += programSize;
	if(adrr >=memory.size()){
		throw std::exception{ "Out range in memory" };
	}
	return memory[adrr];
}
char RamMemory::readFromProgramMemory(int adrr)
{
	if(adrr >=memory.size()){
		throw std::exception{ "Out range in memory" };
	}
	return memory[adrr];
}

void RamMemory::writeInDataMemory(int adrr, char value)
{
	adrr += programSize;
	if (adrr >= memory.size()) {
		throw std::exception{ "Cant write (outside memory)" };
	}
	memory[adrr] = value;
}

void RamMemory::writeInProgramMemory(int adrr, char value)
{
	if (adrr >= memory.size()) {
		throw std::exception{ "Cant write (outside memory)" };
	}
	memory[adrr] = value;
}

void RamMemory::printProgram()
{
	/*for (int i = 0; i < programSize; ++i) {
		std::cout << std::setw(2) << i << "|";
	}*/
	std::cout << std::endl;
	for (char s : memory) {
		std::cout << std::setw(2) << s << "|";
	}
}

void RamMemory::printMemory()
{
	/*int size = memory.size();
	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(2) << i << "|";
	}*/
	std::cout << std::endl;
	for (char s:memory) {
		std::cout << std::setw(2) << s << "|";
	}
}
