#pragma once
#include"../Interpreter/Interpreter.hpp"
#include"../ProcessManager/Process.hpp"
#include<queue>
#include<list>

#define ProcessList std::list<std::shared_ptr<PCB>>

class Scheduler
{
	std::shared_ptr<Interpreter> interpreter;
	std::shared_ptr<ProcessList> activeRunProcess, expiredRunProcess;
public:
	Scheduler();
	~Scheduler();

	void era();
	void moveProcessToExpired(int programCounter);

};

