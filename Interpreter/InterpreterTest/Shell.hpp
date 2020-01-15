#pragma once
#include"PCB.hpp"
#include"../Interpreter/Interpreter.hpp"
#include"ConsoleCommandCreator.hpp"
class Shell
{
	std::unique_ptr<Interpreter> shellInterpreter;

	bool endShell;
	std::shared_ptr<ConsoleCommandCreator> command;
public:
	std::shared_ptr<PCB> pcb;
	std::unique_ptr<Interpreter> pcbInterpreter;

	bool debug;
	Shell();
	Shell(std::shared_ptr<PCB> process);

	void getCommand();
	void doCommand();


	bool isEndShell() const;
};

