#include <iostream>
#include <string>
#include <list>
#include "ProcessManager.hpp"
#include "Process.hpp"


extern PCB* runningProcess;

ProcessManager::ProcessManager()
{
	this->processCounter = processCounter;
}


void ProcessManager::createInitProcess()
{
	processCounter++;
	std::shared_ptr<PCB> newProcess = std::make_shared<PCB>("init","init");
	newProcess->PID = processCounter;
	newProcess->parent = nullptr;
	allProcesses.push_back(newProcess);
	readyProcesses.push_back(newProcess);
	runningProcess = newProcess;
}


void ProcessManager::createProcess(std::string processName, std::string fileName)
{
	processCounter++;
	std::shared_ptr<PCB> newProcess = std::make_shared<PCB>(processName, fileName);
	newProcess->PID = processCounter;
	newProcess->parent = findProcess(1);
	newProcess->parent->children.push_back(newProcess);
	//readyProcesses.push_back(newProcess);
	allProcesses.push_back(newProcess);
	//runningProcess = newProcess;
}


void ProcessManager::displayAllProcesses()
{
	if (allProcesses.empty() == true)
	{
		std::cout << "Lista jest pusta.\n";
	}
	else
	{
	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::displayReadyProcesses()
{
	if (readyProcesses.empty() == true)
	{
		std::cout << "Lista jest pusta.\n";
	}
	else
	{
		for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::removeProcess(unsigned int PID)
{
	if (PID == 1)
	{
		std::cout << "Nie mozna usunac procesu 'init'.\n";
	}
	else if (ifProcessExists(PID) == false)
	{
		std::cout << "Nie znaleziono wskazanego procesu.\n";
	}
	else
	{
		PCB* process = findProcess(PID);
		if (process->state == waiting)
		{
			std::cout << "Nie mozna usunac procesu ze statusem 'waiting'.\n";
		}
		else if (process->children.empty() == true)
		{
			removeProcessFromReady(PID);
			process->parent->children.remove(process);
			allProcesses.remove(process);
			//metoda zwalniajaca przydzielony RAM procesowi, zwalnianie ramu
		}
		else
		{
			std::cout << "*** to-do jak proces ma dzieci, przepiac dzieci z listy dzieci do dziadka ***\n";
		}
	}
}


PCB* ProcessManager::findProcess(unsigned int PID)
{
	for (auto it : allProcesses)
	{
		if (it->getPID() == PID)
		{
			return it;
			break;
		}
	}
}


bool ProcessManager::ifProcessExists(unsigned int PID)
{
	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
	{
		if ((*it)->getPID() == PID)
		{
			return true;
			break;
		}
	}
	return false;
}


void ProcessManager::removeProcessFromReady(unsigned int PID)
{
	PCB* process = findProcess(PID);
	readyProcesses.remove(process);
}


void ProcessManager::removeProcessFromWaiting(unsigned int PID)
{
	PCB* process = findProcess(PID);
	waitingProcesses.remove(process);
}


void ProcessManager::setWaitingStatusToProcess(unsigned int PID)
{
	PCB* process = findProcess(PID);
	process->state = waiting;
	waitingProcesses.push_back(process);
}


void ProcessManager::setReadyStatusToProcess(unsigned int PID)
{
	PCB* process = findProcess(PID);
	process->state = ready;
	readyProcesses.push_back(process);
}