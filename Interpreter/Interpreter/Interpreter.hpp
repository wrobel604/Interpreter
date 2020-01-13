#pragma once
#include<map>
#include"Interfaces/AssembleCommandFactoryInterface.hpp"
#include"Interfaces/AssembleCommandReaderInterface.hpp"

class Interpreter
{
	std::map<std::string, std::unique_ptr<AssembleCommandInterface>> functionList;
public:
	std::unique_ptr<AssembleCommandFactoryInterface> commandFactory;
	std::shared_ptr<AssembleCommandReaderInterface> commandReader;


	Interpreter();

	int step();
};

