#pragma once
#include"../AssemblerTranslator.hpp"

namespace command {
	class CreateFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class SetPosition : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class GetPosition : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class OpenFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class CloseFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class ReadCharFromFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class WriteCharToFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class AppendCharToFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
}