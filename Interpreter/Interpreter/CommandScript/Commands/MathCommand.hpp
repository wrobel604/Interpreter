#pragma once
#include"../AssemblerTranslator.hpp"

namespace command {
	class Addition : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) + this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
	class Subtraction : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) - this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
	class Multiplication : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) * this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
	class Division : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			if (this->getValue(args[1], pcb) != 0) {
				int result = this->getValue(args[0], pcb) / this->getValue(args[1], pcb);
				pcb->setDX(result);
				pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			}
			else { throw std::exception("Divided by 0"); }

			return startArgs + argv;
		}
	};
	class Modulo : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			if (this->getValue(args[1], pcb) != 0) {
				int result = this->getValue(args[0], pcb) % this->getValue(args[1], pcb);
				pcb->setDX(result);
				pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			}
			else { throw std::exception("Divided by 0"); }
			return startArgs + argv;
		}
	};
	class Incrementation : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			
			this->setValue(args[0], this->getValue(args[0], pcb)+1, pcb);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), this->getValue(args[0], pcb)));

			return startArgs + argv;
		}
	};
	class Decrementation : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }

			this->setValue(args[0], this->getValue(args[0], pcb) - 1, pcb);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), this->getValue(args[0], pcb)));

			return startArgs + argv;
		}
	};
	class And : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) & this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
	class Or : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) | this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
	class Xor : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) ^ this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
	class Not : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			pcb->setDX(~this->getValue(args[0], pcb));
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), this->getValue(args[0], pcb)));
			return startArgs + argv;
		}
	};
	class MLF : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) << this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
	class MRT : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 2;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = this->getValue(args[0], pcb) >> this->getValue(args[1], pcb);
			pcb->setDX(result);
			pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
			return startArgs + argv;
		}
	};
}