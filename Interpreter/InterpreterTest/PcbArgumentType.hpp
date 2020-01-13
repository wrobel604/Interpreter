#pragma once
#include"PCB.hpp"

#define PF 1
#define LF 1<<1
#define SF 1<<2
#define CF 1<<3
#define TF 1<<4

struct PcbArgumentType
{
	enum class Type : char{
		Value,
		Flag,
		Ptr,
		CodePtr,
		AX, BX, CX, DX,
		Unknown
	};
	Type type;
	int value;
	std::shared_ptr<PCB> pcb;

	PcbArgumentType(std::shared_ptr<PCB>& Pcb, std::string argument);
};

