#include "Shell.hpp"
#include<iostream>
#include"ShellCommandFactory.hpp"
Shell::Shell()
{
	endShell = false;
	debug = false;
	pcbInterpreter = std::make_unique<Interpreter>();
	shellInterpreter = std::make_unique<Interpreter>();
	pcb = nullptr;
	shellInterpreter->commandFactory = std::make_unique<ShellCommandFactory>();
	command = std::make_shared<ConsoleCommandCreator>();
	command->object = this;
	shellInterpreter->commandReader = command;
}

Shell::Shell(std::shared_ptr<PCB> process) : Shell()
{
	process->state = PCB::processState::active;
	pcbInterpreter->commandReader = process;
}

void Shell::getCommand()
{
	command->writeCommand();
}

void Shell::doCommand()
{
	try {
		if (shellInterpreter->step()) {
			endShell = true;
		}
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	
}

bool Shell::isEndShell() const
{
	return endShell;
}
