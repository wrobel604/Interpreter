#pragma once
#include<map>
#include"PCB.hpp"
#include"AssemblerCommandFactory.hpp"

class Interpreter
{
protected:
	Flags flags;
	
	static std::map<std::string, std::unique_ptr<AssembleCommandInterface>> functionList;
public:
	std::shared_ptr<PCB> pcb;
	static std::unique_ptr<AssemblerCommandFactory> commandFactory;

	Interpreter(std::shared_ptr<PCB>& pcb_ptr);
	~Interpreter();

	char step(char instructionPosition);
	char stepWithDebug(char instructionPosition);

	std::shared_ptr<PCB>& getPCB();
	const Flags& getFlags() const;
};

