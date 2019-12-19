#pragma once
#include"RamMemory.hpp"
#include<string>
#include<fstream>

class ProgramLoader
{
public:
	static void loadProgramToMemory(std::string filename, RamMemory& memory) {
		int programsize = 0;
		std::string bufor;
		std::ifstream in(filename);
		if (in.is_open()) {
			while (in >> bufor) {
				for (char& i : bufor) { memory.writeInProgramMemory(programsize++, i); }
				memory.writeInProgramMemory(programsize++, ' ');
			}
			memory.programSize = programsize;
		}
		in.close();
	}
};