#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include <fstream>
#include <vector>
#include <string>
#include "RAM.hpp"

#define ArraySize 32 //tymczasowy ram

enum processState
{
	active = 0, waiting = 1, ready = 2, terminated = 3
};


class PCB
{
public:
	int PID;
	processState state;
	std::string processName;
	std::string fileName;
	unsigned int processCounter;

	//Numer rozkazu do wykonania, gdy proces dostanie przydział do procesora
	int step;
	int priority;

	PCB(std::string processName, std::string fileName);
	PCB* parent;
	std::list<PCB*> children;
	int getPID();
	void displayProcess();
	std::string getProcessName();
	void displayChildren(unsigned int PID); 

	bool isOutRange(char adrr)
	{
		return adrr >= 0 && adrr < ArraySize;
	}

	//bool status = true; ta zmienna zastępowała zmienną state
	std::shared_ptr<std::vector<std::string>> program;

	PCB() //tym zajmie sie osoba od ramu
	{
		program = std::make_shared<std::vector<std::string>>();
		ram = std::make_shared<RamInterface>(32);
		step = 0;
	}

	static std::shared_ptr<PCB> loadProgramFromFile(std::string fileName)
	{
		std::shared_ptr<PCB> result = std::make_shared<PCB>();
		std::string bufor;
		std::ifstream input(fileName);
		if (input.good() == true)
		{
			while (input >> bufor)
			{
				result->program->push_back(bufor);
			}
			input.close();
			return result;
		}
		else
		{
			std::cout << "Nie znaleziono wskazanego pliku lub plik jest uszkodzony.";
		}
	}

	//Pamięć będzie przydzielana przez moduł zarządzania RAM, więc metody zapisu i odczytu z pamięci będą obsługiwane przez inną klasę
	std::shared_ptr<RamInterface> ram;
	void printMemory()
	{
		int size = ram->getMemorySize();
		for (int i = 0; i < size; ++i) { std::cout << static_cast<int>(ram->readFromMemory(i)) << "|"; }
	}
};
