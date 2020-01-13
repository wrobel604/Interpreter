#pragma once
#include"../AssemblerCommandInterface.hpp"
#include"ArgumentType.hpp"

class AssemblerTranslator : public AssembleCommandInterface {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) = 0;
	virtual std::vector<ArgumentType> loadArgs(char argv, char startPos, std::shared_ptr<PCB>& pcb) {
		std::vector<ArgumentType> result;
		std::string buf = "";
		for (int i = 0; i < argv; ++i) {
			buf = AssembleCommandInterface::loadWordFromPcb(startPos + i, pcb);
			startPos += buf.size();
				//pcb->program->at(startPos + i);
			switch (buf[0])
			{
			case '\'': result.push_back(ArgumentType{ ArgumentType::Type::Value, buf[1] }); break;
			case '[':
				switch (buf[1])
				{
				case 'A':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->getAX() }); break;
				case 'B':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->getBX() }); break;
				case 'C':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->getCX() }); break;
				case 'D':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->getDX() }); break;
				default:
					result.push_back(ArgumentType{ ArgumentType::Type::Ptr, NumberConversion::stringToCharNumber(buf.substr(1, buf.size() - 2)) });
					break;
				}break;
			case '{': 
				switch (buf[1]) {
				case 'A': result.push_back(ArgumentType{ ArgumentType::Type::CodePtr, pcb->getAX() }); break;
				case 'B': result.push_back(ArgumentType{ ArgumentType::Type::CodePtr, pcb->getBX() }); break;
				case 'C': result.push_back(ArgumentType{ ArgumentType::Type::CodePtr, pcb->getCX() }); break;
				case 'D': result.push_back(ArgumentType{ ArgumentType::Type::CodePtr, pcb->getDX() }); break;
				default:
					result.push_back(ArgumentType{ ArgumentType::Type::CodePtr, NumberConversion::stringToCharNumber(buf.substr(1, buf.size() - 2)) });
				}
				break;
			case 'A': result.push_back(ArgumentType{ ArgumentType::Type::AX, pcb->getAX() }); break;
			case 'B': result.push_back(ArgumentType{ ArgumentType::Type::BX, pcb->getBX() }); break; break;
			case 'C':
				if (buf[1] == 'X') {
					result.push_back(ArgumentType{ ArgumentType::Type::CX, pcb->getCX() });
				}
				else
				{
					result.push_back(ArgumentType{ ArgumentType::Type::Flags, Flags::getFlag(pcb->getFlags(), CF) });
				}
				break;
			case 'D': result.push_back(ArgumentType{ ArgumentType::Type::DX, pcb->getDX() }); break; 
			case 'P': result.push_back(ArgumentType{ ArgumentType::Type::Flags, Flags::getFlag(pcb->getFlags(), PF) }); break;
			case 'L': result.push_back(ArgumentType{ ArgumentType::Type::Flags, Flags::getFlag(pcb->getFlags(), LF) }); break;
			case 'S': result.push_back(ArgumentType{ ArgumentType::Type::Flags, Flags::getFlag(pcb->getFlags(), SF) }); break;
			case 'W': result.push_back(ArgumentType{ ArgumentType::Type::Flags, Flags::getFlag(pcb->getFlags(), TF) }); break;
			default:
				result.push_back(ArgumentType{ ArgumentType::Type::Value, (char)atoi(buf.c_str()) });
				break;
			}
		}
		return result;
	}
	virtual char getValue(ArgumentType& args, std::shared_ptr<PCB>& pcb) {
		switch (args.getType())
		{
		case ArgumentType::Type::Flags:
		case ArgumentType::Type::Value:
			return args.getValue(); break;
		case ArgumentType::Type::AX: 
		case ArgumentType::Type::BX: 
		case ArgumentType::Type::CX: 
		case ArgumentType::Type::DX: 
			return args.getValue(); break;
		case ArgumentType::Type::Ptr: return pcb->readFromDataMemory(args.getValue()); break;
		case ArgumentType::Type::CodePtr: return pcb->readFromProgramMemory(args.getValue()); break;
		default:
			break;
		}
		return -1;
	}
	virtual void setValue(ArgumentType& args, char value, std::shared_ptr<PCB>& pcb) {
		switch (args.getType())
		{
		case ArgumentType::Type::AX: pcb->setAX(value); break;
		case ArgumentType::Type::BX:pcb->setBX(value); break;
		case ArgumentType::Type::CX:pcb->setCX(value); break;
		case ArgumentType::Type::DX:pcb->setDX(value); break;
		case ArgumentType::Type::Ptr: pcb->writeInDataMemory(args.getValue(), value); break;
		case ArgumentType::Type::CodePtr: pcb->writeInProgramMemory(args.getValue(), value); break;
		default:
			break;
		}
	}
	virtual int ArgumentLength(int argc, int startPos, std::shared_ptr<PCB>& pcb);
};