#pragma once
#include<vector>
#include<exception>

class RamMemory
{
	friend class ProgramLoader;

	std::vector<char> memory;
	int programSize;
public:
	RamMemory(int ram = 1024);

	int getMemorySize() const;
	int getProgramSize() const;

	char readFromDataMemory(int adrr);
	char readFromProgramMemory(int adrr);

	void writeInDataMemory(int adrr, char value);
	void writeInProgramMemory(int adrr, char value);

	void printProgram();
	void printMemory();
};

