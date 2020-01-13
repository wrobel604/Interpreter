#include "ConsoleCommandCreator.hpp"
#include<iostream>

ConsoleCommandCreator::ConsoleCommandCreator()
{
	commandIndex = 0;
	commands.clear();
}

std::string ConsoleCommandCreator::getCommand()
{
	return (commandIndex<commands.size())? commands[commandIndex++]:"";
}

void ConsoleCommandCreator::writeCommand()
{
	commands.clear();
	std::string bufor = "";
	std::cout << "> ";
	while (std::cin.peek() != '\n') {
		std::cin >> bufor;
		for (char& c : bufor) { c = std::tolower(c); }
		commands.push_back(bufor);
	}
	std::cin.ignore();
	commandIndex = 0;
}
