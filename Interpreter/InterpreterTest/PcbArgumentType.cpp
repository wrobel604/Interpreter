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
			value = (pcb->Registers.Flag & CF) == CF;
		}
	}break;
	case 'D': {
		type = Type::DX;
		value = pcb->Registers.DX;
	}break;
	case 'P': {
		type = Type::Flag;
		value = (pcb->Registers.Flag & PF)  == PF; 
	}break;
	case 'L': {
		type = Type::Flag;
		value = (pcb->Registers.Flag & LF) == LF; 
	}break;
	case 'S': {
		type = Type::Flag;
		value = (pcb->Registers.Flag & SF) == SF; 
	}break;
	case 'Z': {
		type = Type::Flag;
		value = (pcb->Registers.Flag & ZF) == ZF; 
	}break;
	case '0': {
		type = Type::Value;
		switch (argument[1])
		{
		case 'b': value = NumberConversion::BinToDec(argument.substr(2)); return;
		case 'o': value = NumberConversion::OctToDec(argument.substr(2)); return;
		case 'x': value = NumberConversion::HexToDec(argument.substr(2)); return;
		default:
			break;
		}
	}
	default:
		value = atoi(argument.c_str());
		break;
	}
}

void PcbArgumentType::write(char val)
{
	switch (type)
	{
	case Type::AX: pcb->Registers.AX= val; break;
	case Type::BX: pcb->Registers.BX= val; break;
	case Type::CX: pcb->Registers.CX= val; break;
	case Type::DX: pcb->Registers.DX= val; break;
	case Type::CodePtr:pcb->writeInProgramMemory(value, val); break;
	case Type::Ptr:pcb->writeInDataMemory(value, val); break;
	default:
		break;
	}
}

char PcbArgumentType::read() const
{
	switch (type)
	{
	case Type::Ptr: return pcb->readFromDataMemory(value);
	case Type::CodePtr: return pcb->readFromProgramMemory(value);
	default:
		break;
	}
	return value;
}
