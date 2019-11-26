#pragma once
#include"AssemblerCommandInterface.hpp"

class AssemblerCommandFactory
{
public:
	virtual std::unique_ptr<AssembleCommandInterface> addCommand(std::string commandName);
};

