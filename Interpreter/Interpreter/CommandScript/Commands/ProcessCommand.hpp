#pragma once
#include "../../Interpreter.hpp"
#include"../AssemblerTranslator.hpp"

namespace command {
	class CreateSyncProcess : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) {
			char argv = 1;
			std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
			if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
			std::string programName = std::string{ getValue(args[0], pcb) };
			std::shared_ptr<PCB> child = std::make_unique<PCB>(programName);
			Interpreter inter{ child };
			char step = 0;
			while (child->state == processState::active) {
				step = inter.step(step);
			}
			return startArgs + argv;
		}
	};
}