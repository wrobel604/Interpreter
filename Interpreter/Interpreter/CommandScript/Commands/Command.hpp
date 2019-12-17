#pragma once
#include"../AssemblerTranslator.hpp"
namespace command {
	class SetValue : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
};
	class JumpIfNotZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
};
	class JumpIfZero : public AssemblerTranslator {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
};
	class IF : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class End : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class Click : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
}
