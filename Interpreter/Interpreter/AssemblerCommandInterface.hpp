#pragma once
#include<string>
#include<vector>
#include<memory>
#include"Flags.hpp"
#include"PCB.hpp"
#include"Conversion.hpp"

class AssembleCommandInterface {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) = 0;
};