#include "ConsoleCommandCreator.hpp"
#include<iostream>

ConsoleCommandCreator::ConsoleCommandCreator()
{
	commandIndex = 0;
	commands.clear();
	object = nullptr;
}

std::string ConsoleCommandCreator::getCommand()
{
	if (commandIndex == 0) { for (char& i : commands[0]) { i = std::tolower(i); } }
	return (commandIndex<commands.size())? commands[commandIndex++]:"";
}

void ConsoleCommandCreator::writeCommand()
{
	commands.clear();
	std::string bufor = "";
	std::cout << "> ";
	while (std::cin.peek() != '\n') {
		std::cin >> bufor;
		commands.push_back(bufor);
	}
	std::cin.ignore();
	commandIndex = 0;
}
