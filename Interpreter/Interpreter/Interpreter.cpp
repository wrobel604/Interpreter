#include "Interpreter.hpp"
#include<iostream>
#include<exception>


Interpreter::Interpreter()
{
	commandFactory = std::make_unique<AssemblerCommandFactory>();
}

Interpreter::Interpreter(std::shared_ptr<PCB>& pcb_ptr) : Interpreter()
{
	this->pcb = pcb_ptr;
}

Interpreter::~Interpreter()
{
}

int Interpreter::step()
{
	int result = 0;
	std::string command = AssembleCommandInterface::loadWordFromPcb(pcb->instrucionCounter, pcb);
	if(functionList.find(command)==functionList.end()){
		bool isAdded = false;
		if (Interpreter::commandFactory != nullptr) {
			functionList[command] = commandFactory->addCommand(command); 
		}
		if (functionList[command] == nullptr) {
			throw std::exception{ std::string{"Cannot load function " + command + "\n"}.c_str() };
		}
	}
	pcb->instrucionCounter = functionList[command]->doCommand(pcb, pcb->instrucionCounter + command.size() + 1);
	return pcb->instrucionCounter;
}

int Interpreter::stepWithDebug()
{
	std::string command = AssembleCommandInterface::loadWordFromPcb(pcb->instrucionCounter, pcb);
	std::cout << "Command: " << command << "\nDisplay: ";
	int result = step();
	std::cout << "\nArguments: ";
	pcb->instrucionCounter += command.size();
	for (int i = pcb->instrucionCounter + 1; i < result; ++i) {
		command = AssembleCommandInterface::loadWordFromPcb(pcb->instrucionCounter, pcb);
		std::cout << command <<" ";
		pcb->instrucionCounter += command.size();
	}
	std::cout << "\nRegisters:\n\tAX = " << static_cast<int>(pcb->getAX()) << "\n\t";
	std::cout << "BX = " << static_cast<int>(pcb->getBX()) << "\n\t";
	std::cout << "CX = " << static_cast<int>(pcb->getCX()) << "\n\t";
	std::cout << "DX = " << static_cast<int>(pcb->getDX()) << "\n";
	std::cout << "Flags:\n\tPF = " << Flags::getFlag(pcb->getFlags(), PF) << "\n\t";
	std::cout << "LF = " << Flags::getFlag(pcb->getFlags(), LF) << "\n\t";
	std::cout << "SF = " << Flags::getFlag(pcb->getFlags(), SF) << "\n\t";
	std::cout << "CF = " << Flags::getFlag(pcb->getFlags(), CF) << "\n";
	std::cout << "WF = " << Flags::getFlag(pcb->getFlags(), TF) << "\n";
	std::cout << "Memory: ";
	pcb->printMemory();
	std::cout << "\nNext adress: " << result << "\n";
	if (result < pcb->getMemorySize()) {
		std::cout << "Next command: " << AssembleCommandInterface::loadWordFromPcb(result, pcb) << "\n";
	}
	else {
		std::cout << "No next command\n";
	}
	return result;
}

std::shared_ptr<PCB>& Interpreter::getPCB()
{
	return this->pcb;
}
