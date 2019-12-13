#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Process.hpp"



class ProcessManager
{
public:
	//runningProcess jako zmienna statyczna będzie lepiej widoczna dla innych osób
	static std::shared_ptr<PCB> runningProcess;
	//int createChildProcess(int parentPID, std::string processName, std::string fileName);
	//

	std::list<PCB*> allProcesses;
	std::list<PCB*> readyProcesses;
	std::list<PCB*> waitingProcesses;
	unsigned int processCounter = 0;
	ProcessManager();

	void createProcess(std::string processName, std::string fileName);
	void createInitProcess();
	void displayAllProcesses();
	void displayReadyProcesses();
	void removeProcess(unsigned int PID);
	bool ifProcessExists(unsigned int PID);
	PCB* findProcess(unsigned int PID);
	void removeProcessFromWaiting(unsigned int PCB);
	void removeProcessFromReady(unsigned int PCB);
	void setWaitingStatusToProcess(unsigned int PID);
	void setReadyStatusToProcess(unsigned int PID);
	void setTerminatedStatusToProcess(unsigned int PID);
};
