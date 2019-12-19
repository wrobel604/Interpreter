#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<regex>
#include"ProgramLoader.hpp"
#include<fstream>

enum class processState : char
{
	active = 0, waiting = 1, ready = 2, terminated = 3
};
class PCB {
	static int processNumber;
	int PID;
	std::string processName;
	std::string programfileName;
	char AX, BX, CX, DX, Flag;
	std::shared_ptr<RamMemory> memory;
	int programSize;
public:

	processState state;
	std::shared_ptr<PCB> parent;
	int instrucionCounter = 0;

	std::string fileName;

	PCB();
	PCB(std::string program_adrr);
	PCB(std::string processname, std::string program_adrr);
	
	int getPID() const;
	const std::string& getProcessName() const;

	void writeInDataMemory(int adrr, char value);
	void writeInProgramMemory(int adrr, char value);
	char readFromDataMemory(int adrr);
	char readFromProgramMemory(int adrr);
	char getAX() const;
	char getBX() const;
	char getCX() const;
	char getDX() const;
	char getFlags() const;

	void setAX(char value); //ustawia wartosc value w danym rejestrze
	void setBX(char value);
	void setCX(char value);
	void setDX(char value);
	void setFlags(char value);

	int getMemorySize() const;
	void printMemory();
	void printProgram();
};