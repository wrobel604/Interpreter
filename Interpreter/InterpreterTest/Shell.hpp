#pragma once
#include"PCB.hpp"
#include"../Interpreter/Interpreter.hpp"
#include"ConsoleCommandCreator.hpp"
#include<list>
class Shell
{
	std::unique_ptr<Interpreter> shellInterpreter;

	bool endShell;
	std::shared_ptr<ConsoleCommandCreator> command;
	std::shared_ptr<PCB> dummy;
	std::list<std::shared_ptr<PCB>> pcbQueue;
public:
	std::unique_ptr<Interpreter> pcbInterpreter;

	bool debug;
	Shell();
	Shell(std::shared_ptr<PCB> process);

	void getCommand();
	void doCommand();

	bool addProcessToQueue(std::shared_ptr<PCB> process);
	std::shared_ptr<PCB> removeProcessFromQueue();

	bool isDummy() const;
	std::shared_ptr<PCB> getDummy();
	bool isEndShell() const;
};

