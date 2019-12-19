#pragma once
#include"../Interpreter/Interpreter.hpp"
class Shell
{
	std::shared_ptr<PCB> pcb;
	std::unique_ptr<Interpreter> interpreter;

	std::vector<std::string> command;
	bool endShell;
public:
	bool debug;
	Shell();
	Shell(std::shared_ptr<PCB> process);

	void getCommand();
	void doCommand();

	bool isEndShell() const;
};

