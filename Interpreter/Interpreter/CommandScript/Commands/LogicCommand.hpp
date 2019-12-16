#pragma once
#include"../AssemblerTranslator.hpp"

namespace command {
	class Equal : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = (this->getValue(args[0], pcb) == this->getValue(args[1], pcb));
			//std::cout <<"|" << result << "|\n";
			pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
			return startArgs + argv;
		}
	};
	class Less : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = (this->getValue(args[0], pcb) < this->getValue(args[1], pcb));
			pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
			return startArgs + argv;
		}
	};
	class More : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = (this->getValue(args[0], pcb) > this->getValue(args[1], pcb));
			pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
			return startArgs + argv;
		}
	};
	class MoreOrEqual : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = (this->getValue(args[0], pcb) >= this->getValue(args[1], pcb));
			pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
			return startArgs + argv;
		}
	};
	class LessOrEqual : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = (this->getValue(args[0], pcb) <= this->getValue(args[1], pcb));
			pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
			return startArgs + argv;
		}
	};
}