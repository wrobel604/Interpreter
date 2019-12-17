#include "AssemblerCommandFactory.hpp"
#include"Commands/Command.hpp"
#include"Commands/MathCommand.hpp"
#include"Commands/LogicCommand.hpp"
#include"Commands/ConsoleCommand.hpp"

std::unique_ptr<AssembleCommandInterface> AssemblerCommandFactory::addCommand(std::string commandName)
{
	//Math
	if (commandName == "ADD") { return std::make_unique<command::Addition>(); }
	if (commandName == "SUB") { return std::make_unique<command::Subtraction>(); }
	if (commandName == "MUL") { return std::make_unique<command::Multiplication>(); }
	if (commandName == "DIV") { return std::make_unique<command::Division>(); }
	if (commandName == "MOD") { return std::make_unique<command::Modulo>(); }
	if (commandName == "AND") { return std::make_unique<command::And>(); }
	if (commandName == "OR") { return std::make_unique<command::Or>(); }
	if (commandName == "XOR") { return std::make_unique<command::Xor>(); }
	if (commandName == "NOT") { return std::make_unique<command::Not>(); }
	if (commandName == "MLF") { return std::make_unique<command::MLF>(); }
	if (commandName == "MRT") { return std::make_unique<command::MRT>(); }
	if (commandName == "INC") { return std::make_unique<command::Incrementation>(); }
	if (commandName == "DEC") { return std::make_unique<command::Decrementation>(); }
	//Other
	if (commandName == "SET") { return std::make_unique<command::SetValue>(); }
	if (commandName == "JMP") { return std::make_unique<command::JumpIfNotZero>(); }
	if (commandName == "JPZ") { return std::make_unique<command::JumpIfZero>(); }
	if (commandName == "IF") { return std::make_unique<command::IF>(); }

	
	//Logic
	if (commandName == "EQL") { return std::make_unique<command::Equal>(); }
	if (commandName == "LSS") { return std::make_unique<command::Less>(); }
	if (commandName == "MOR") { return std::make_unique<command::More>(); }
	if (commandName == "LSE") { return std::make_unique<command::LessOrEqual>(); }
	if (commandName == "MRE") { return std::make_unique<command::MoreOrEqual>(); }
	//Console
	if (commandName == "OUT") { return std::make_unique<command::ConsoleWriteLetter>(); }
	if (commandName == "ONR") { return std::make_unique<command::ConsoleWriteNumber>(); }
	if (commandName == "MOT") { return std::make_unique<command::ConsoleWriteWords>(); }
	if (commandName == "IN") { return std::make_unique<command::ConsoleRead>(); }
	if (commandName == "INS") { return std::make_unique<command::ConsoleReadChar>(); }
	if (commandName == "END") { return std::make_unique<command::End>(); }
	if (commandName == "CLK") { return std::make_unique<command::Click>(); }

	return nullptr;
}
