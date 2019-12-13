#include "Process.hpp"
#include "ProcessManager.hpp"
#include <list>
#include <iostream>

extern std::list<PCB*> allProcesses;
extern PCB* runningProcess;

PCB::PCB(std::string processName, std::string filename)
{
	this->PID = processCounter;
	this->processName = processName;
	this->state = active;
	this->fileName = filename + ".txt";
	this->state = ready;
	//loadProgramFromFile(fileName); //odczyt programu z pliku
}

int PCB::getPID()
{
	return PID;
}

void PCB::displayProcess()
{
	std::string sState;
	switch (state)
	{
	case 0:
		sState = "Active";
		break;
	case 1:
		sState = "Waiting";
		break;
	case 2:
		sState = "Ready";
		break;
	case 3:
		sState = "Terminated";
		break;
	}

	std::cout << "PID: " << PID << " | File name: " << fileName << " | Process name: " << processName << " | State: " << sState << "\n";
}


std::string PCB::getProcessName()
{
	return processName;
}


void PCB::displayChildren(unsigned int PID)
{
	for (auto child : children)
	{
		child->displayProcess();
	}
}