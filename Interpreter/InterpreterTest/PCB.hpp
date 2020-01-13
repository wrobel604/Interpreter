#pragma once
#include"../Interpreter/Interfaces/AssembleCommandReaderInterface.hpp"
#include"RamMemory.hpp"
#include<memory>

class PCB : public AssembleCommandReaderInterface
{
public:
	enum class processState : char {
		active, waiting, ready, terminated
	};
private:
	std::shared_ptr<RamMemory> ram;
	int programSize;
public:
	struct {
		char AX, BX, CX, DX, Flag;
	} Registers;
	processState state;

	PCB(std::string processName);

	void writeInDataMemory(int adrr, char value);
	void writeInProgramMemory(int adrr, char value);
	char readFromDataMemory(int adrr);
	char readFromProgramMemory(int adrr);

	int getMemorySize() const;

	// Inherited via AssembleCommandReaderInterface
	virtual std::string getCommand() override;
};

