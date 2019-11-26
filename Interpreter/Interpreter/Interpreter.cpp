#include "Interpreter.hpp"
#include<iostream>
#include<exception>

std::unique_ptr<AssemblerCommandFactory> Interpreter::commandFactory = std::make_unique<AssemblerCommandFactory>();
std::map<std::string, std::unique_ptr<AssembleCommandInterface>> Interpreter::functionList = std::map<std::string, std::unique_ptr<AssembleCommandInterface>>{};

Interpreter::Interpreter(std::shared_ptr<PCB>& pcb_ptr)
{
	this->pcb = pcb_ptr;
	Flags::setFlags(flags,0);
}

Interpreter::~Interpreter()
{
}

char Interpreter::step(char instructionPosition, bool debug)
{
	int result = 0;
	std::string command = pcb->program->at(instructionPosition);
	if(functionList.find(command)==functionList.end()){
		bool isAdded = false;
		if (commandFactory != nullptr) {
			functionList[command] = commandFactory->addCommand(command); 
		}
		if (functionList[command] == nullptr) {
			throw std::exception{"Cannot load function\n"};
		}
	}
	if (debug) {
		std::cout << "Command: " << command << "\nResult: ";
	}
	result = functionList[command]->doCommand(pcb, flags, instructionPosition + 1);
	if (debug) {
		std::cout << "\nArgument(s): ";
		for (int i = instructionPosition + 1; i < result; ++i) {
			std::cout<< pcb->program->at(i) <<" ";
		}
		std::cout << "\nRegisters:\n\tAX = " << static_cast<int>(pcb->getAX()) << "\n";
		std::cout<<"\tBX = " << static_cast<int>(pcb->getBX()) << "\n";
		std::cout<<"\tCX = " << static_cast<int>(pcb->getCX()) << "\n";
		std::cout<<"\tDX = " << static_cast<int>(pcb->getDX()) << "\n";
		std::cout << "Flags:\n\tLF = " << flags.getFlag(LF) << "\n";
		std::cout << "\tPF = " << flags.getFlag(PF) << "\n";
		std::cout << "\tSF = " << flags.getFlag(SF) << "\n";
		std::cout << "\tCF = " << flags.getFlag(CF) << "\n";
		if (result < pcb->program->size()) {
			std::cout << "Next step: " << pcb->program->at(result) << "\n";
		}
		else {
			std::cout << "Program terminated\n";
		}
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
