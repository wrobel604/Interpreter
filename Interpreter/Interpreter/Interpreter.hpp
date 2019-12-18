#pragma once
#include<map>
#include"CommandScript/AssemblerCommandFactory.hpp"

class Interpreter
{
protected:
	std::map<std::string, std::unique_ptr<AssembleCommandInterface>> functionList;
public:
	std::shared_ptr<PCB> pcb;
	std::unique_ptr<AssemblerCommandFactory> commandFactory;

	Interpreter();
	Interpreter(std::shared_ptr<PCB>& pcb_ptr);
	~Interpreter();

	int step();
	int stepWithDebug();

	std::shared_ptr<PCB>& getPCB();
};

