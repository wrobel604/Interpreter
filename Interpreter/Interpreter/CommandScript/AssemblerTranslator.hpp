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
			buf = pcb->program->at(startPos + i);
			switch (buf[0])
			{
			case '\'': result.push_back(ArgumentType{ ArgumentType::Type::Value, buf[1] }); break;
			case '[':
				switch (buf[1])
				{
				case 'A':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->readFromMemory(pcb->getAX()) }); break;
				case 'B':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->readFromMemory(pcb->getAX()) }); break;
				case 'C':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->readFromMemory(pcb->getAX()) }); break;
				case 'D':result.push_back(ArgumentType{ ArgumentType::Type::Ptr, pcb->readFromMemory(pcb->getAX()) }); break;
				default:
					result.push_back(ArgumentType{ ArgumentType::Type::Ptr, NumberConversion::stringToCharNumber(buf.substr(1, buf.size() - 2)) });
					break;
				}break;
			case '{': 
				switch (buf[1]) {
				case 'A': result.push_back(ArgumentType{ ArgumentType::Type::Value, NumberConversion::stringToCharNumber(pcb->program->at(pcb->getAX())) }); break;
				case 'B': result.push_back(ArgumentType{ ArgumentType::Type::Value, NumberConversion::stringToCharNumber(pcb->program->at(pcb->getBX())) }); break;
				case 'C': result.push_back(ArgumentType{ ArgumentType::Type::Value, NumberConversion::stringToCharNumber(pcb->program->at(pcb->getCX())) }); break;
				case 'D': result.push_back(ArgumentType{ ArgumentType::Type::Value, NumberConversion::stringToCharNumber(pcb->program->at(pcb->getDX())) }); break;
				default:
					std::string val = pcb->program->at(NumberConversion::stringToCharNumber(buf.substr(1, buf.size() - 2)));
					if(val[0]=='\''){ result.push_back(ArgumentType{ ArgumentType::Type::Value, val[1] }); }else
					result.push_back(ArgumentType{ ArgumentType::Type::Value, NumberConversion::stringToCharNumber(val) });
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
		case ArgumentType::Type::Ptr: return pcb->readFromMemory(args.getValue()); break;
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
		case ArgumentType::Type::Ptr: pcb->writeInMemory(args.getValue(), value); break;
		default:
			break;
		}
	}
};