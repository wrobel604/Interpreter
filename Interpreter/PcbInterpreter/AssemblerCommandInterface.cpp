#include "AssemblerCommandInterface.hpp"

std::string AssembleCommandInterface::loadWordFromPcb(int startPosition, std::shared_ptr<PCB>& pcb)
{
	std::string result = "";
	char sign;
	while (startPosition<pcb->getMemorySize() && (sign = pcb->readFromProgramMemory(startPosition++)) != ' ') {
		result += sign;
	}
	return result;
}
