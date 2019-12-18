#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<regex>
#include<fstream>

enum class processState : char
{
	active = 0, waiting = 1, ready = 2, terminated = 3
};
class PCB {
	int PID;
	std::string processName;
	std::string fileName;
	char AX, BX, CX, DX, Flag;
	std::vector<char> memory;
	int programSize;
public:

	processState state;
	std::shared_ptr<PCB> parent;
	int instrucionCounter = 0;

	PCB() { 
		state = processState::ready;
		AX = BX = CX = DX = Flag = 0;
	}
	PCB(std::string program_adrr) : PCB() {
		std::string bufor;
		std::ifstream in(program_adrr);
		if (in.is_open()) {
			while (in >> bufor) {
				for (char& i : bufor) { memory.push_back(i); }
				memory.push_back(' ');
			}
			programSize = getMemorySize();
			for(int i=0;i<10;++i){ memory.push_back(' '); }
		}
		in.close();
	}
	
	void writeInDataMemory(int adrr, char value){
		this->memory[adrr+programSize] = value;
	}
	void writeInProgramMemory(int adrr, char value){
		this->memory[adrr] = value;
	}
	char readFromDataMemory(char adrr){
		return memory[adrr + programSize];
	}
	char readFromProgramMemory(char adrr){
		return memory[adrr];
	}
	char getAX() const { return AX; }
	char getBX() const { return BX; }
	char getCX() const { return CX; }
	char getDX() const { return DX; }
	char getFlags() const { return Flag; }

	void setAX(char value) { AX = value; } //ustawia wartosc value w danym rejestrze
	void setBX(char value) { BX = value; }
	void setCX(char value) { CX = value; }
	void setDX(char value) { DX = value; }
	void setFlags(char value) { Flag = value; }

	int getMemorySize() const { return memory.size(); }
	void printMemory() {
		for (char& i: memory) { std::cout<<i <<"|"; }
	}
};