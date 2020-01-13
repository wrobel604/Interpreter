#pragma once
#include"../AssemblerTranslator.hpp"

namespace command {
	class Addition : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Subtraction : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Multiplication : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Division : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Modulo : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Incrementation : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Decrementation : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class And : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Or : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Xor : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Not : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class MLF : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class MRT : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
}