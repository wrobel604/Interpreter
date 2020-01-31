#include "Shell.hpp"
#include<iostream>
#include"ShellCommandFactory.hpp"
#include"PcbCommandFactory.hpp"
Shell::Shell()
{
	endShell = false;
	debug = false;
	pcbInterpreter = std::make_unique<Interpreter>();
	pcbInterpreter->commandFactory = std::make_unique<PcbCommandFactory>();
	shellInterpreter = std::make_unique<Interpreter>();
	dummy = std::make_shared<PCB>("dummy");
	shellInterpreter->commandFactory = std::make_unique<ShellCommandFactory>();
	command = std::make_shared<ConsoleCommandCreator>();
	command->object = this;
	shellInterpreter->commandReader = command;
}

Shell::Shell(std::shared_ptr<PCB> process) : Shell()
{
	process->state = PCB::processState::active;
	addProcessToQueue(process);
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

bool Shell::addProcessToQueue(std::shared_ptr<PCB> process)
{
	if (process != nullptr) {
		pcbQueue.push_back(process);
		return true;
	}
	return false;
}

std::shared_ptr<PCB> Shell::removeProcessFromQueue()
{
	if (pcbQueue.empty()) { return nullptr; }
	std::shared_ptr<PCB> res = std::move(pcbQueue.front());
	pcbQueue.pop_front();
	return res;
}

bool Shell::isDummy() const
{
	return pcbInterpreter->commandReader == dummy;
}

std::shared_ptr<PCB> Shell::getDummy()
{
	return dummy;
}

bool Shell::isEndShell() const
{
	return endShell;
}
