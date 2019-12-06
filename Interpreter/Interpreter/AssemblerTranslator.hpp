#pragma once
#include"AssemblerCommandInterface.hpp"

class AssemblerTranslator : public AssembleCommandInterface {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) = 0;
	
	enum class ArgumentType : char {
		RegisterAX = 0, 
		RegisterBX = 1, 
		RegisterCX = 2, 
		RegisterDX = 3,
		ParityFlag,
		LogicFlag,
		SignFlag,
		CarryFlag,
		AdressInMemory,
		AdressInProgram,
		Number,
		Unknow
	};

	virtual std::vector<char> loadArgs(char argv, char startPos, std::shared_ptr<PCB>& pcb, Flags& flags) {
		std::vector<char> result;
		std::string buf = "";
		for (int i = 0; i < argv; ++i) {
			buf = pcb->program->at(startPos + i);
			switch (buf[0])
			{
			case '\'': result.push_back(buf[1]); break;
			case '{':
				switch (buf[1])
				{
				case 'A':result.push_back(loadArgs(1, pcb->getAX(), pcb, flags)[0]);  break;
				case 'B':result.push_back(loadArgs(1, pcb->getBX(), pcb, flags)[0]); break;
				case 'C':result.push_back(loadArgs(1, pcb->getCX(), pcb, flags)[0]); break;
				case 'D':result.push_back(loadArgs(1, pcb->getDX(), pcb, flags)[0]); break;
				default:
					result.push_back(loadArgs(1, Conversion::string_to_charNumber(buf.substr(1, buf.size() - 2)), pcb, flags)[0]);
					break;
				}break;
			case '[':
				switch (buf[1])
				{
				case 'A':result.push_back(pcb->readFromMemory(pcb->getAX())); break;
				case 'B':result.push_back(pcb->readFromMemory(pcb->getAX())); break;
				case 'C':result.push_back(pcb->readFromMemory(pcb->getAX())); break;
				case 'D':result.push_back(pcb->readFromMemory(pcb->getAX())); break;
				default:
					result.push_back(pcb->readFromMemory(Conversion::string_to_charNumber(buf.substr(1, buf.size() - 2))));
					break;
				}break;
			case 'A': result.push_back(pcb->getAX()); break;
			case 'B': result.push_back(pcb->getBX()); break;
			case 'C':
				if (buf[1] == 'X')
					result.push_back(pcb->getCX());
				else
					result.push_back(flags[CF]);
				break;
			case 'D': result.push_back(pcb->getDX()); break;
			case 'P': result.push_back(flags[PF]); break;
			case 'L': result.push_back(flags[LF]); break;
			case 'S': result.push_back(flags[SF]); break;
			default:
				result.push_back(Conversion::string_to_charNumber(buf));
				break;
			}
		}
		return result;
	}
};