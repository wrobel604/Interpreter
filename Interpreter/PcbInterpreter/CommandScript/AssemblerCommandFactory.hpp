#pragma once
#include"../AssemblerCommandFactoryInterface.hpp"

class AssemblerCommandFactory : public AssemblerCommandFactoryInterface
{
public:
	virtual std::unique_ptr<AssembleCommandInterface> addCommand(std::string commandName);
};

