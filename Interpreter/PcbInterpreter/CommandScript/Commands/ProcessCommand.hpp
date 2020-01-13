#pragma once
#include "../../Interpreter.hpp"
#include"../AssemblerTranslator.hpp"

namespace command {
	class CreateSyncProcess : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
}