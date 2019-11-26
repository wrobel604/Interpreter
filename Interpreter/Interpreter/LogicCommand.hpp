#pragma once
#include"AssemblerCommandInterface.hpp"

namespace command {
	class Equal : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = (args[0] == args[1]);
			//std::cout <<"|" << result << "|\n";
			flags.setFlag(LF, result);
			return startArgs + argv;
		}
	};
	class Less : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = args[0] < args[1];
			flags.setFlag(LF, result);
			return startArgs + argv;
		}
	};
	class More : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = args[0] > args[1];
			flags.setFlag(LF, result);
			return startArgs + argv;
		}
	};
	class MoreOrEqual : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = args[0] >= args[1];
			flags.setFlag(LF, result);
			return startArgs + argv;
		}
	};
	class LessOrEqual : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, Flags& flags, char startArgs = 0) {
			char argv = 2;
			std::vector<char> args = this->loadArgs(argv, startArgs, pcb, flags);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			bool result = args[0] <= args[1];
			flags.setFlag(LF, result);
			return startArgs + argv;
		}
	};
}