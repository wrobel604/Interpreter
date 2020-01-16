#include "PcbCommandFactory.hpp"
#include"PcbCommands.hpp"

std::unique_ptr<AssembleCommandInterface> PcbCommandFactory::getCommand(std::string commandname)
{
	if (commandname == "OUT") {
		return std::make_unique<ConsoleWriteLetter>();
	}
	if (commandname == "ONR") {
		return std::make_unique<ConsoleWriteNumber>();
	}
	if (commandname == "END") {
		return std::make_unique<EndProgram>();
	}
	if (commandname == "SET") {
		return std::make_unique<SetValue>();
	}
	if (commandname == "ADD") {
		return std::make_unique<Addition>();
	}
	if (commandname == "SUB") {
		return std::make_unique<Subtraction>();
	}
	if (commandname == "MUL") {
		return std::make_unique<Multiplication>();
	}
	if (commandname == "DIV") {
		return std::make_unique<Division>();
	}
	if (commandname == "MOD") {
		return std::make_unique<Modulo>();
	}
	if (commandname == "INC") {
		return std::make_unique<Incrementation>();
	}
	if (commandname == "DEC") {
		return std::make_unique<Decrementation>();
	}
	if (commandname == "AND") {
		return std::make_unique<And>();
	}
	if (commandname == "OR") {
		return std::make_unique<Or>();
	}
	if (commandname == "XOR") {
		return std::make_unique<Xor>();
	}
	if (commandname == "NOT") {
		return std::make_unique<Not>();
	}
	if (commandname == "MLF") {
		return std::make_unique<LeftBitMove>();
	}
	if (commandname == "MRT") {
		return std::make_unique<RightBitMove>();
	}
	if (commandname == "EQL") {
		return std::make_unique<Equal>();
	}
	if (commandname == "LSS") {
		return std::make_unique<Less>();
	}
	if (commandname == "LSE") {
		return std::make_unique<Less>();
	}
	if (commandname == "MOR") {
		return std::make_unique<More>();
	}
	if (commandname == "MRE") {
		return std::make_unique<More>();
	}
	if (commandname == "JMP") {
		return std::make_unique<JumpIfTrue>();
	}
	if (commandname == "JMZ") {
		return std::make_unique<JumpIfFalse>();
	}
	return nullptr;
}
