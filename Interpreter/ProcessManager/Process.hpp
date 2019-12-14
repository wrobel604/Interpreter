#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include <fstream>
#include <vector>
#include <string>
#include "RAM.hpp"

#define ArraySize 32 //tymczasowy ram

enum processState
{
	active = 0, waiting = 1, ready = 2, terminated = 3
};


class PCB
{
public:
	int PID;
	processState state;
	std::string processName;
	std::string fileName;
	int processCounter;
	PCB* parent;
	std::list<PCB*> children;
	std::shared_ptr<RamInterface> ram;

	std::shared_ptr<std::vector<std::string>> program;
	//Numer rozkazu do wykonania, gdy proces dostanie przydział do procesora
	int priority;

	PCB();
	PCB(std::string processName, std::string fileName);

	int getPID() const;
	void displayProcess();
	std::string getProcessName();
	void displayChildren(unsigned int PID); 
	void loadProgramFromFile();
	
	void printMemory()
	{
		int size = ram->getMemorySize();
		for (int i = 0; i < size; ++i) { std::cout << static_cast<int>(ram->readFromMemory(i)) << "|"; }
	}
};
