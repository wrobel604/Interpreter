#include "PCB.hpp"
#include<fstream>
#include<string>
PCB::PCB(std::string processName)
{
	programSize = commandIndex = 0;
	Registers.AX = Registers.BX = Registers.CX = Registers.DX = Registers.Flag;
	ram = std::make_shared<RamMemory>();
	state = processState::ready;
	std::string bufor;
	std::ifstream in(processName+".txt");
	if (in.is_open()) {
		while (in >> bufor) {
			for (char& i : bufor) {
				ram->write(programSize++, i); }
			ram->write(programSize++, ' ');
		}
	in.close();
	}
	else {
		throw std::exception("No program data");
	}
}

void PCB::writeInDataMemory(int adrr, char value)
{
	ram->write(adrr + programSize, value);
}

void PCB::writeInProgramMemory(int adrr, char value)
{
	ram->write(adrr, value);
}

char PCB::readFromDataMemory(int adrr)
{
	return ram->read(adrr+programSize);
}

char PCB::readFromProgramMemory(int adrr)
{
	return ram->read(adrr);
}

int PCB::getMemorySize() const
{
	return ram->getSize();
}

std::string PCB::getCommand()
{
	std::string result = "";
	char sign;
	while ((sign = readFromProgramMemory(commandIndex++)) != ' ') {
		result += sign;
	}
	return result;
}
