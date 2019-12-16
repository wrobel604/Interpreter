#pragma once
#include"../AssemblerTranslator.hpp"
namespace command {
	class SetValue : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
		char argv = 2;
		std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		if (args[0].getType() != ArgumentType::Type::Value && args[0].getType() != ArgumentType::Type::Unknown) {
			this->setValue(args[0], this->getValue(args[1], pcb), pcb);
		}
		return startArgs + argv;
	}
};
	class JumpIfNotZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
		char argv = 1;
		std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		return (Flags::getFlag(pcb->getFlags(), LF))? this->getValue(args[0],pcb):(startArgs+argv);
	}
};
	class JumpIfZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
		char argv = 1;
		std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
		if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
		return (!Flags::getFlag(pcb->getFlags(), LF))? this->getValue(args[0], pcb) :(startArgs+argv);
	}
};
	class IF : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, this->getValue(args[0], pcb)));
			return startArgs+argv;
		}
	};
	class End : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			pcb->state = processState::terminated;
			if (pcb->parent != nullptr && Flags::getFlag(pcb->getFlags(), WF)) {
				pcb->parent->state = processState::ready;
			}
			return startArgs;
		}
	};
	class Click : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			std::cin.get();
			return startArgs;
		}
	};
}
