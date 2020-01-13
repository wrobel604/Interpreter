#include"PCB.hpp"

int PCB::processNumber = 0;

PCB::PCB() {
	PID = processNumber++;
	state = processState::ready;
	AX = BX = CX = DX = Flag = 0;
	memory = std::make_shared<RamMemory>();
	fileName = "";
}

PCB::PCB(std::string program_adrr) : PCB() {
	programfileName = program_adrr;
	ProgramLoader::loadProgramToMemory(programfileName, *memory);
}

PCB::PCB(std::string processname, std::string program_adrr) : PCB() {
	processName = processname;
	programfileName = program_adrr;
	ProgramLoader::loadProgramToMemory(programfileName, *memory);
}

int PCB::getPID() const
{
	return PID;
}

const std::string& PCB::getProcessName() const
{
	return this->processName;
}

void PCB::writeInDataMemory(int adrr, char value) {
	this->memory->writeInDataMemory(adrr, value);
}

void PCB::writeInProgramMemory(int adrr, char value) {
	this->memory->writeInDataMemory(adrr, value);
}

char PCB::readFromDataMemory(int adrr) {
	return memory->readFromDataMemory(adrr);
}

char PCB::readFromProgramMemory(int adrr) {
	return memory->readFromProgramMemory(adrr);
}

char PCB::getAX() const { return AX; }

char PCB::getBX() const { return BX; }

char PCB::getCX() const { return CX; }

char PCB::getDX() const { return DX; }

char PCB::getFlags() const { return Flag; }

void PCB::setAX(char value) { AX = value; }

void PCB::setBX(char value) { BX = value; }

void PCB::setCX(char value) { CX = value; }

void PCB::setDX(char value) { DX = value; }

void PCB::setFlags(char value) { Flag = value; }

int PCB::getMemorySize() const { return memory->getMemorySize(); }

void PCB::printMemory() {
	memory->printMemory();
}

void PCB::printProgram() { memory->printProgram(); }
