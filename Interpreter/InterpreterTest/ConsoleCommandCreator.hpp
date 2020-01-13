#pragma once
#include"../Interpreter/Interfaces/AssembleCommandReaderInterface.hpp"
#include<vector>

class ConsoleCommandCreator : public AssembleCommandReaderInterface
{
	std::vector<std::string> commands;
public:
	ConsoleCommandCreator();
	// Inherited via AssembleCommandReaderInterface
	virtual std::string getCommand() override;
	void writeCommand();

	void* object;
};

