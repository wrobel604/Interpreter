#pragma once
#include"../AssemblerTranslator.hpp"
#include<iostream>

namespace command {
	class ConsoleWriteLetter : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			std::cout << this->getValue(args[0], pcb);
			return startArgs + argv;
		}
	};
	class ConsoleWriteNumber : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			std::cout << static_cast<int>(this->getValue(args[0], pcb));
			return startArgs + argv;
		}
	};
	class ConsoleWriteWords : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			ConsoleWriteLetter write;
			int size = this->getValue(args[0], pcb);
			for (int i = 0; i < size; ++i) {
				write.doCommand(pcb, startArgs + argv + i);
			}
			return startArgs + argv + size;
		}
	};
	class ConsoleRead : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			std::string text;
			int value = 0;
			std::cin >> text; std::cin.ignore();
			
			pcb->setBX(NumberConversion::stringToCharNumber(text));
			return startArgs;
		}
	};
	class ConsoleReadChar : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char sign;
			std::cin >> sign; std::cin.ignore();
			pcb->setBX(sign);
			return startArgs;
		}
	};
}