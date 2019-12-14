#pragma once
#include"AssemblerTranslator.hpp"

namespace command {
	class Addition : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] + args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class Subtraction : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] - args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class Multiplication : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] * args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class Division : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			if (args[1] != 0) {
				int result = args[0] / args[1];
				pcb->ram->setDX(result);
				Flags::setFlags(flags, result);
				return startArgs;
			}
			else { throw std::exception("Divided by 0"); }

			return startArgs + argv;
		}
	};
	class Modulo : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			if (args[1] != 0) {
				int result = args[0] % args[1];
				pcb->ram->setDX(result);
				Flags::setFlags(flags, result);
				return startArgs;
			}
			else { throw std::exception("Divided by 0"); }
			return startArgs + argv;
		}
	};
	class Incrementation : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			
			int result = ++args[0];
			//pcb->ram->setDX(result);
			std::string toWriteAdress = pcb->program->at(startArgs);
			switch (toWriteAdress[0])
			{
			case '[': pcb->writeInMemory(Conversion::string_to_charNumber(toWriteAdress.substr(1, toWriteAdress.size() - 2)), result); break;
			case 'A': pcb->setAX(result); break;
			case 'B': pcb->setBX(result); break;
			case 'C': pcb->setCX(result); break;
			case 'D': pcb->ram->setDX(result); break;
			default:
				pcb->ram->setDX(result);
				break;
			}
			Flags::setFlags(flags, result);

			return startArgs + argv;
		}
	};
	class Decrementation : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = --args[0];
			//pcb->ram->setDX(result);
			std::string toWriteAdress = pcb->program->at(startArgs);
			switch (toWriteAdress[0])
			{
			case '[': pcb->writeInMemory(Conversion::string_to_charNumber(toWriteAdress.substr(1, toWriteAdress.size() - 2)), result); break;
			case 'A': pcb->setAX(result); break;
			case 'B': pcb->setBX(result); break;
			case 'C': pcb->setCX(result); break;
			case 'D': pcb->ram->setDX(result); break;
			default:
				pcb->ram->setDX(result);
				break;
			}
			Flags::setFlags(flags, result);

			return startArgs + argv;
		}
	};
	class And : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] & args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class Or : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] | args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class Xor : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] ^ args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class Not : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = ~args[0];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class MLF : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] << args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
	class MRT : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			int result = args[0] >> args[1];
			pcb->ram->setDX(result);
			Flags::setFlags(flags, result);
			return startArgs + argv;
		}
	};
}