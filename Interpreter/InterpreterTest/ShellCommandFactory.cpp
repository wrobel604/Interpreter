#include "ShellCommandFactory.hpp"
#include"ShellCommands.hpp"

std::unique_ptr<AssembleCommandInterface> ShellCommandFactory::getCommand(std::string commandname)
{
	if (commandname == "create") {
		return std::make_unique<CreateProcess>();
	}
	if(commandname == "kill"){
		return std::make_unique<KillProcess>();
	}
	if(commandname == "step"){
		return std::make_unique<StepProcess>();
	}
	if(commandname == "steps"){
		return std::make_unique<StepAllProcess>();
	}
	if(commandname == "memory"){
		return std::make_unique<MemoryPrint>();
	}
	if(commandname == "set"){
		return std::make_unique<ChangeMemory>();
	}
	if(commandname == "registers"){
		return std::make_unique<RegistersPrint>();
	}
	if(commandname == "debug"){
		return std::make_unique<DebugFlag>();
	}
	if(commandname == "exit"){
		return std::make_unique<ExitShell>();
	}
	if(commandname == "help"){
		return std::make_unique<HelpPrint>();
	}
	if(commandname == "pos"){
		return std::make_unique<StepIndex>();
	}
	return nullptr;
}
