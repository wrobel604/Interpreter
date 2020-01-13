#include "PcbCommandFactory.hpp"

std::unique_ptr<AssembleCommandInterface> PcbCommandFactory::getCommand(std::string commandname)
{
	if (commandname == "JMP") {

	}
	return nullptr;
}
