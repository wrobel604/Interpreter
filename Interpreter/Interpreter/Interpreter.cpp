#include "Interpreter.hpp"
#include<iostream>
#include<exception>

std::map<std::string, std::unique_ptr<AssembleCommandInterface>> Interpreter::functionList = std::map<std::string, std::unique_ptr<AssembleCommandInterface>>{};
std::unique_ptr<AssemblerCommandFactory> Interpreter::commandFactory = std::make_unique<AssemblerCommandFactory>();

Interpreter::Interpreter()
{
	Flags::setFlags(flags, 0);
}

Interpreter::Interpreter(std::shared_ptr<PCB>& pcb_ptr)
{
	this->pcb = pcb_ptr;
	Flags::setFlags(flags,0);
}

Interpreter::~Interpreter()
{
}

char Interpreter::step(char instructionPosition)
{
	int result = 0;
	std::string command = pcb->program->at(instructionPosition);
	if(functionList.find(command)==functionList.end()){
		bool isAdded = false;
		if (Interpreter::commandFactory != nullptr) {
			functionList[command] = commandFactory->addCommand(command); 
		}
		if (functionList[command] == nullptr) {
			throw std::exception{"Cannot load function\n"};
		}
	}
	result = functionList[command]->doCommand(pcb, flags, instructionPosition + 1);
	return result;
}

char Interpreter::stepWithDebug(char instructionPosition)
{
	std::cout << "Command: " << pcb->program->at(instructionPosition) << "\nResult: ";
	int result = step(instructionPosition);
	std::cout << "\nArguments: ";
	for (int i = instructionPosition + 1; i < result; ++i) {
		std::cout << pcb->program->at(i);
	}
	std::cout << "\nRegisters:\n\tAX = " << static_cast<int>(pcb->getAX()) << "\n\t";
	std::cout << "BX = " << static_cast<int>(pcb->getBX()) << "\n\t";
	std::cout << "CX = " << static_cast<int>(pcb->getCX()) << "\n\t";
	std::cout << "DX = " << static_cast<int>(pcb->getDX()) << "\n";
	std::cout << "Flags:\n\tPF = " << flags.getFlag(PF) << "\n\t";
	std::cout << "LF = " << flags.getFlag(LF) << "\n\t";
	std::cout << "SF = " << flags.getFlag(SF) << "\n\t";
	std::cout << "CF = " << flags.getFlag(CF) << "\n";
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

const Flags& Interpreter::getFlags() const
{
	return flags;
}
