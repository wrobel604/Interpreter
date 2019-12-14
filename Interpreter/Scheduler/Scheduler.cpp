#include "Scheduler.hpp"

Scheduler::Scheduler()
{
	interpreter = std::make_shared<Interpreter>();
	activeRunProcess = std::make_unique<ProcessList>();
	expiredRunProcess = std::make_unique<ProcessList>();
}

Scheduler::~Scheduler()
{
}

void Scheduler::era()
{
	interpreter->pcb = activeRunProcess->front();
	activeRunProcess->pop_front();
	int eraCouter = 0;
	while (interpreter->pcb->state == processState::active) {
		interpreter->pcb->processCounter = interpreter->step(interpreter->pcb->processCounter);
		++eraCouter;
	}
	if (interpreter->pcb->state != processState::terminated) {
		moveProcessToExpired(eraCouter);
	}
	if (activeRunProcess->empty()) {
		std::swap(activeRunProcess, expiredRunProcess);
	}
}

void Scheduler::moveProcessToExpired(int programCounter)
{
	//ustalenie nowego priorytetu dynamicznego dla procesu
	//int newPriority = 120 
	if (expiredRunProcess->empty()) {
		expiredRunProcess->push_back(interpreter->pcb);
	}
	else {
		for (ProcessList::iterator it = expiredRunProcess->begin; it != expiredRunProcess->end();++it) {
			if (interpreter->pcb->priority < (*it)->priority) {
				expiredRunProcess->insert(it, interpreter->pcb); return;
			}
			expiredRunProcess->push_back(interpreter->pcb);
		}
	}
}
