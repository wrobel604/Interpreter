#include "PcbCommandFactory.hpp"
#include"PcbCommands.hpp"

std::unique_ptr<AssembleCommandInterface> PcbCommandFactory::getCommand(std::string commandname)
{
	//OUT value
	if (commandname == "OUT") {
		return std::make_unique<ConsoleWriteLetter>();
	}
	//ONR value
	if (commandname == "ONR") {
		return std::make_unique<ConsoleWriteNumber>();
	}
	//END
	if (commandname == "END") {
		return std::make_unique<EndProgram>();
	}
	//SET where value
	if (commandname == "SET") {
		return std::make_unique<SetValue>();
	}
	//ADD value value
	if (commandname == "ADD") {
		return std::make_unique<Addition>();
	}
	//SUB value value
	if (commandname == "SUB") {
		return std::make_unique<Subtraction>();
	}
	//MUL value value
	if (commandname == "MUL") {
		return std::make_unique<Multiplication>();
	}
	//DIV value value
	if (commandname == "DIV") {
		return std::make_unique<Division>();
	}
	//MOD value value
	if (commandname == "MOD") {
		return std::make_unique<Modulo>();
	}
	//INC value
	if (commandname == "INC") {
		return std::make_unique<Incrementation>();
	}
	//DEC value
	if (commandname == "DEC") {
		return std::make_unique<Decrementation>();
	}
	//AND value value
	if (commandname == "AND") {
		return std::make_unique<And>();
	}
	//OR value value
	if (commandname == "OR") {
		return std::make_unique<Or>();
	}
	//XOR value value
	if (commandname == "XOR") {
		return std::make_unique<Xor>();
	}
	//NOT value
	if (commandname == "NOT") {
		return std::make_unique<Not>();
	}
	//MLF value value
	if (commandname == "MLF") {
		return std::make_unique<LeftBitMove>();
	}
	//MRT value value
	if (commandname == "MRT") {
		return std::make_unique<RightBitMove>();
	}
	//EQL value value
	if (commandname == "EQL") {
		return std::make_unique<Equal>();
	}
	//LSS value value
	if (commandname == "LSS") {
		return std::make_unique<Less>();
	}
	//LSE value value
	if (commandname == "LSE") {
		return std::make_unique<Less>();
	}
	//MOR value value
	if (commandname == "MOR") {
		return std::make_unique<More>();
	}
	//MRE value value
	if (commandname == "MRE") {
		return std::make_unique<More>();
	}
	//JMP value
	if (commandname == "JMP") {
		return std::make_unique<JumpIfTrue>();
	}
	//JMZ value
	if (commandname == "JMZ") {
		return std::make_unique<JumpIfFalse>();
	}
	//CRF filename
	if (commandname == "CRF") {
		return std::make_unique<CreateFile>();
	}
	//OPF filename
	if (commandname == "OPF") {
		return std::make_unique<OpenFile>();
	}
	//CLF filename
	if (commandname == "CLF") {
		return std::make_unique<CloseFile>();
	}
	//RCF filename
	if (commandname == "RCF") {
		return std::make_unique<ReadCharFile>();
	}
	//RSF filename count memory_index
	if (commandname == "RSF") {
		return std::make_unique<ReadCharsFile>();
	}
	//WCF filename value
	if (commandname == "WCF") {
		return std::make_unique<WriteCharFile>();
	}
	//WSF filename count memory_index
	if (commandname == "WSF") {
		return std::make_unique<WriteCharsFile>();
	}
	//GPF filename
	if (commandname == "GPF") {
		return std::make_unique<GetPositionFile>();
	}
	//SPF filename value
	if (commandname == "SPF") {
		return std::make_unique<SetPositionFile>();
	}
	//IEF filename
	if (commandname == "IEF") {
		return std::make_unique<IsExistFile>();
	}
	return nullptr;
}
