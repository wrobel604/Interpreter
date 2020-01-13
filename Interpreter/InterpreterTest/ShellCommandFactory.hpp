#pragma once
#include"../Interpreter/Interfaces/AssembleCommandFactoryInterface.hpp"
class ShellCommandFactory : public AssembleCommandFactoryInterface
{
public:
	// Inherited via AssembleCommandFactoryInterface
	virtual std::unique_ptr<AssembleCommandInterface> getCommand(std::string commandname) override;
};

