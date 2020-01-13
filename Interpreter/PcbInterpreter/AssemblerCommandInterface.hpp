#pragma once
#include<string>
#include<vector>
#include<memory>
#include"Flags.hpp"
#include"Modules/PCB.hpp"
#include"Conversion.hpp"

class AssembleCommandInterface {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) = 0;

	static std::string loadWordFromPcb(int startPosition, std::shared_ptr<PCB>& pcb);
};