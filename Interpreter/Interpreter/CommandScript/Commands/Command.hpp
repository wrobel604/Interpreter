#pragma once
#include"../AssemblerTranslator.hpp"
namespace command {
	class SetValue : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
		char argv = 2;
		std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb, flags);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		if (args[0].getType() != ArgumentType::Type::Value && args[0].getType() != ArgumentType::Type::Unknown) {
			this->setValue(args[0], this->getValue(args[1], pcb), pcb);
		}
		return startArgs + argv;
	}
};
	class JumpIfNotZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
		char argv = 1;
		std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb, flags);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		return (flags.getFlag(LF))? this->getValue(args[0],pcb):(startArgs+argv);
	}
};
	class JumpIfZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
		char argv = 1;
		std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb, flags);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		return (!flags.getFlag(LF))? this->getValue(args[0], pcb) :(startArgs+argv);
	}
};
	class IF : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			flags.setFlag(LF, this->getValue(args[0], pcb));
			return startArgs+argv;
		}
	};
	class End : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			pcb->state = PCB::ProcessState::terminated;
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
