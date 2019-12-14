#pragma once
#include"AssemblerTranslator.hpp"
namespace command {
	class SetValue : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
		char argv = 2;
		std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		std::string toWriteAdress = pcb->program->at(startArgs);
		switch (toWriteAdress[0])
		{
		case '[': 
			switch (toWriteAdress[1])
			{
			case 'A': pcb->ram->writeInMemory(pcb->ram->getAX(), args[1]); break;
			case 'B': pcb->ram->writeInMemory(pcb->ram->getBX(), args[1]); break;
			case 'C': pcb->ram->writeInMemory(pcb->ram->getCX(), args[1]); break;
			case 'D': pcb->ram->writeInMemory(pcb->ram->getDX(), args[1]); break;
			default:
				pcb->ram->writeInMemory(Conversion::string_to_charNumber(toWriteAdress.substr(1, toWriteAdress.size() - 2)), args[1]);
				break;
			}
			break;
		case 'A': pcb->ram->setAX(args[1]); break;
		case 'B': pcb->ram->setBX(args[1]); break;
		case 'C': {
			if (toWriteAdress[1] == 'X')
				pcb->ram->setCX(args[1]);
			else
				flags.setFlag(CF, args[1]);
		} break;
		case 'D': pcb->ram->setDX(args[1]); break;
		case 'P': flags.setFlag(PF, args[1]); return startArgs + argv; break;
		case 'L': flags.setFlag(LF, args[1]); return startArgs + argv; break;
		case 'S': flags.setFlag(SF, args[1]); return startArgs + argv; break;
		default:
			
			break;
		}
		Flags::setFlags(flags, args[1]);
		return startArgs + argv;
	}
};
	class JumpIfNotZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
		char argv = 1;
		std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		return (flags.getFlag(LF))? args[0]:(startArgs+argv);
	}
};
	class JumpIfZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
		char argv = 1;
		std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		return (!flags.getFlag(LF))? args[0]:(startArgs+argv);
	}
};
	class IF : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			flags.setFlag(LF, args[0]);
			return startArgs+argv;
		}
	};
	class End : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			pcb->state = processState::terminated;
			return startArgs;
		}
	};
	class Click : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			std::cin.get();
			return startArgs;
		}
	};
}
