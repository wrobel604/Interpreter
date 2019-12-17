#pragma once
#include"AssemblerCommandInterface.hpp"

class AssemblerCommandFactoryInterface
{
public:
	virtual std::unique_ptr<AssembleCommandInterface> addCommand(std::string commandName) = 0;
};