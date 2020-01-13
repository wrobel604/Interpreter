#include "PcbCommands.hpp"
#include"PCB.hpp"
#include<iostream>

int ConsoleWriteLetter::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	std::string text = pcb->getCommand();
	return 0;
}
