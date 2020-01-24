#pragma once
#include"../Interpreter/Interfaces/AssembleCommandReaderInterface.hpp"
#include"RamMemory.hpp"
#include<memory>
#include"FileManager.hpp"

class PCB : public AssembleCommandReaderInterface
{
public:
	struct Register{
		char AX=0, BX=0, CX=0, DX=0, Flag=0;
		void setFlag(char index, bool value);
		bool getFlag(char index);
	};
	enum class processState : char {
		active, waiting, ready, terminated
	};
private:
	std::shared_ptr<RamMemory> ram;
	int programSize;
public:
	Register Registers;
	processState state;
	FileManager file;

	PCB(std::string processName);

	void writeInDataMemory(int adrr, char value);
	void writeInProgramMemory(int adrr, char value);
	char readFromDataMemory(int adrr);
	char readFromProgramMemory(int adrr);

	int getMemorySize() const;

	// Inherited via AssembleCommandReaderInterface
	virtual std::string getCommand() override;
};

