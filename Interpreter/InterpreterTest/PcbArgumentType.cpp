#include "PcbArgumentType.hpp"
#include"NumberConversion.hpp"

PcbArgumentType::PcbArgumentType(std::shared_ptr<PCB>& Pcb, std::string argument)
{
	pcb = Pcb;
	if (argument == "") { throw std::exception("No argument"); }
	switch (argument[0])
	{
	case '\'': {
		type = Type::Value;
		value = argument[1];
	}break;
	case '[': {
		type = Type::Ptr;
		std::string subvalue = argument.substr(1, argument.size() - 2);
		PcbArgumentType sub{ pcb, subvalue };
		value = sub.value;
	}break;
	case '{': {
		type = Type::CodePtr;
		std::string subvalue = argument.substr(1, argument.size() - 2);
		PcbArgumentType sub{ pcb, subvalue };
		value = sub.value;
	}break;
	case 'A': {
		type = Type::AX;
		value = pcb->Registers.AX;
	}break;
	case 'B': {
		type = Type::BX;
		value = pcb->Registers.BX;
	}break;
	case 'C': {
		if (argument[1] == 'X') {
			type = Type::CX;
			value = pcb->Registers.CX;
		}
		else if (argument[1] == 'F') {
			type = Type::Flag;
			value = pcb->Registers.Flag & CF;
		}
	}break;
	case 'D': {
		type = Type::DX;
		value = pcb->Registers.DX;
	}break;
	case 'P': {
		type = Type::Flag;
		value = pcb->Registers.Flag & PF; 
	}break;
	case 'L': {
		type = Type::Flag;
		value = pcb->Registers.Flag & LF; 
	}break;
	case 'S': {
		type = Type::Flag;
		value = pcb->Registers.Flag & SF; 
	}break;
	case 'T': {
		type = Type::Flag;
		value = pcb->Registers.Flag & TF; 
	}break;
	case '0': {
		type = Type::Value;
		switch (argument[1])
		{
		case 'b': value = NumberConversion::BinToDec(argument.substr(2)); break;
		case 'o': value = NumberConversion::BinToDec(argument.substr(2)); break;
		case 'x': value = NumberConversion::BinToDec(argument.substr(2)); break;
		default:
			value = atoi(argument.c_str());
			break;
		}
	}
	default:
		
		break;
	}
}
