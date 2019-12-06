#pragma once
#include"AssemblerTranslator.hpp"
#include<iostream>

namespace command {
	class ConsoleWriteLetter : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			std::cout << args[0];
			return startArgs + argv;
		}
	};
	class ConsoleWriteWords : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 1;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			ConsoleWriteLetter write;
			for (int i = 0; i < args[0]; ++i) {
				write.doCommand(pcb, flags, startArgs + argv + i);
			}
			return startArgs + argv + args[0];
		}
	};
	class ConsoleWriteFromMemory : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			//char adrrRes = Conversion::getMemoryAdress(pcb->program->at(startArgs + 1));
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			ConsoleWriteLetter write;
			for (int i = 0; i < args[0]; ++i) {
				write.doCommand(pcb, flags, args[1] + i);
			}
			return startArgs + argv + args[0];
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