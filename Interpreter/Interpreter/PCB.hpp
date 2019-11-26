#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<regex>
#include<fstream>

#define ArraySize 32

class PCB {
	char memory[ArraySize];
	char startIndex = 4;
	
	bool isOutRange(char adrr){ return adrr >= 0 && adrr < ArraySize;}
public:
	std::shared_ptr<std::vector<std::string>> program;

	PCB() { 
		for (int i = 0; i < ArraySize; ++i) { memory[i] = 0; } 
		program = std::make_shared<std::vector<std::string>>(); 
	}
	PCB(std::string code) : PCB() {
		std::regex regex("([A-Za-z]+[0-9]{0,1})|(-{0,1}[1-9]*[0-9]+)");
		std::smatch match;
		while (std::regex_search(code, match, regex)) {
			if (match[1] != "") { program->push_back(match[1]); }
			if (match[2] != "") { program->push_back(match[2]); }
			code = match.suffix();
		}
	}
	PCB(const PCB& pcb) :PCB(){
		startIndex = pcb.startIndex;
		program = pcb.program;
	}
	static PCB loadProgramFromFile(std::string program_adrr) {
		PCB result;
		std::string bufor;
		std::ifstream in(program_adrr);
		while (in >> bufor) {
			result.program->push_back(bufor);
		}
		in.close();
		return result;
	}
	
	void writeInMemory(char adrr, char value){
		adrr += startIndex;
		if (isOutRange(adrr)) { throw std::exception{"Access memory error(write)"}; }
		memory[adrr] = value;
	}
	char readFromMemory(char adrr){
		adrr += startIndex;
		if (isOutRange(adrr)) { throw std::exception{ "Access memory error(read)" }; }
		return memory[adrr];
	}
	char getAX() { return memory[0]; }
	char getBX() { return memory[1]; }
	char getCX() { return memory[2]; }
	char getDX() { return memory[3]; }

	void setAX(char value) { memory[0] = value; }
	void setBX(char value) { memory[1] = value; }
	void setCX(char value) { memory[2] = value; }
	void setDX(char value) { memory[3] = value; }

	void printMemory() {
		for (int i = 0; i < ArraySize; ++i) { std::cout<<static_cast<int>(memory[i]) <<"|"; }
	}
};