#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<regex>
#include<fstream>

#define ArraySize 32
enum processState
{
	active = 0, waiting = 1, ready = 2, terminated = 3
};
class PCB {
	int PID;
	std::string processName;
	std::string fileName;
	char AX, BX, CX, DX, Flag;
	char memory[ArraySize];
public:

	processState state;
	std::shared_ptr<std::vector<std::string>> program; 
	std::shared_ptr<PCB> parent;

	PCB() { 
		for (int i = 0; i < ArraySize; ++i) { memory[i] = 0; } 
		program = std::make_shared<std::vector<std::string>>(); 
		state = processState::active;
		AX = BX = CX = DX = Flag = 0;
	}
	PCB(std::string program_adrr) : PCB() {
		std::string bufor;
		std::ifstream in(program_adrr);
		if (in.is_open()) {
			while (in >> bufor) {
				program->push_back(bufor);
			}
		}
		in.close();
	}
	PCB(const PCB& pcb) :PCB(){
		program = pcb.program;
	}
	static std::shared_ptr<PCB> loadProgramFromFile(std::string program_adrr) {
		std::shared_ptr<PCB> result = std::make_shared<PCB>();
		std::string bufor;
		std::ifstream in(program_adrr);
		while (in >> bufor) {
			result->program->push_back(bufor);
		}
		in.close();
		return result;
	}
	
	void writeInMemory(int adrr, char value){
		this->memory[adrr] = value;
	}
	char readFromMemory(char adrr){
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

	void printMemory() {
		for (int i = 0; i < ArraySize; ++i) { std::cout<<static_cast<int>(memory[i]) <<"|"; }
	}
};