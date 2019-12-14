#pragma once
#include<string>
#include<vector>
#include<memory>
#include"Flags.hpp"
#include"../ProcessManager/Process.hpp"
#include"Conversion.hpp"

class AssembleCommandInterface {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) = 0;
	virtual std::vector<char> loadArgs(char argv, char startPos, std::shared_ptr<PCB>& pcb, Flags& flags) = 0;
};