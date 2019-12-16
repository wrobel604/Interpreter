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

int Interpreter::step(int instructionPosition)
{
	int result = 0;
	std::string command = pcb->program->at(instructionPosition);
	if(functionList.find(command)==functionList.end()){
		bool isAdded = false;
		if (Interpreter::commandFactory != nullptr) {
			functionList[command] = commandFactory->addCommand(command); 
		}
		if (functionList[command] == nullptr) {
			throw std::exception{ std::string{"Cannot load function " + command + "\n"}.c_str() };
		}
	}
	result = functionList[command]->doCommand(pcb, instructionPosition + 1);
	return result;
}

int Interpreter::stepWithDebug(int instructionPosition)
{
	std::cout << "Command: " << pcb->program->at(instructionPosition) << "\nDisplay: ";
	int result = step(instructionPosition);
	std::cout << "\nArguments: ";
	for (int i = instructionPosition + 1; i < result; ++i) {
		std::cout << pcb->program->at(i) <<" ";
	}
	std::cout << "\nRegisters:\n\tAX = " << static_cast<int>(pcb->getAX()) << "\n\t";
	std::cout << "BX = " << static_cast<int>(pcb->getBX()) << "\n\t";
	std::cout << "CX = " << static_cast<int>(pcb->getCX()) << "\n\t";
	std::cout << "DX = " << static_cast<int>(pcb->getDX()) << "\n";
	std::cout << "Flags:\n\tPF = " << Flags::getFlag(pcb->getFlags(), PF) << "\n\t";
	std::cout << "LF = " << Flags::getFlag(pcb->getFlags(), LF) << "\n\t";
	std::cout << "SF = " << Flags::getFlag(pcb->getFlags(), SF) << "\n\t";
	std::cout << "CF = " << Flags::getFlag(pcb->getFlags(), CF) << "\n";
	std::cout << "WF = " << Flags::getFlag(pcb->getFlags(), WF) << "\n";
	std::cout << "Memory: ";
	pcb->printMemory();
	if (result < pcb->program->size()) {
		std::cout << "Next command: " << pcb->program->at(result) << "\n";
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
