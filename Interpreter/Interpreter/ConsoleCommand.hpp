#pragma once
#include"AssemblerTranslator.hpp"
#include<iostream>

namespace command {
	class ConsoleWriteLetter : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			std::cout << this->getValue(args[0], pcb);
			return startArgs + argv;
		}
	};
	class ConsoleWriteWords : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			ConsoleWriteLetter write;
			int size = this->getValue(args[0], pcb);
			for (int i = 0; i < size; ++i) {
				write.doCommand(pcb, flags, startArgs + argv + i);
			}
			return startArgs + argv + size;
		}
	};
	class ConsoleRead : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char value = 0;
			std::cin >> value; std::cin.get();
			pcb->setBX(value);
			return startArgs;
		}
	};
}