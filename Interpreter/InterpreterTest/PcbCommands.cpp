#include "PcbCommands.hpp"
#include"PCB.hpp"
#include"PcbArgumentType.hpp"
#include<iostream>

void setResultFlag(int value, std::shared_ptr<PCB>& pcb) {
	pcb->Registers.setFlag(PF, value & 1);
	pcb->Registers.setFlag(LF, value);
	pcb->Registers.setFlag(SF, static_cast<char>(value)<0);
	pcb->Registers.setFlag(CF, value < -128 || value>127);
	pcb->Registers.setFlag(ZF, value==0);
}

int ConsoleWriteLetter::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	std::string text = pcb->getCommand();
	//std::cout << text << "\n";
	PcbArgumentType arg{ pcb, text };
	std::cout << arg.read();
	return pcb->commandIndex;
}

int ConsoleWriteNumber::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	std::string text = pcb->getCommand();
	PcbArgumentType arg{ pcb, text };
	std::cout << static_cast<int>(arg.read());
	return pcb->commandIndex;
}
int EndProgram::doCommand(std::shared_ptr<AssembleCommandReaderInterface> & reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	pcb->state = PCB::processState::terminated;
	return pcb->commandIndex;
}

int SetValue::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType where{ pcb, pcb->getCommand() }, value{ pcb, pcb->getCommand() };
	where.write(value.read());
	return pcb->commandIndex;
}

int Addition::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() + b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Subtraction::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() - b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Multiplication::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() * b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Division::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() / b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Modulo::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() % b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Decrementation::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() };
	int result = a.read() - 1;
	setResultFlag(result, pcb);
	a.write(result);
	return pcb->commandIndex;
}

int Incrementation::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() };
	int result = a.read() + 1;
	setResultFlag(result, pcb);
	a.write(result);
	return pcb->commandIndex;
}

int And::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() & b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Or::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() | b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Xor::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() ^ b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Not::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() };
	int result = ~a.read();
	a.write(result);
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int LeftBitMove::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() << b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int RightBitMove::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	int result = a.read() >> b.read();
	pcb->Registers.DX = result;
	setResultFlag(result, pcb);
	return pcb->commandIndex;
}

int Equal::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.setFlag(LF, a.read() == b.read());
	return pcb->commandIndex;
}

int Less::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.setFlag(LF, a.read() < b.read());
	return pcb->commandIndex;
}

int More::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.setFlag(LF, a.read() > b.read());
	return pcb->commandIndex;
}

int JumpIfTrue::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType adr{ pcb, pcb->getCommand() };
	return (pcb->Registers.getFlag(LF))? adr.read():pcb->commandIndex;
}

int JumpIfFalse::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType adr{ pcb, pcb->getCommand() };
	return (!pcb->Registers.getFlag(LF)) ? adr.read() : pcb->commandIndex;
}

int LessOrEqual::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.setFlag(LF, a.read() <= b.read());
	return pcb->commandIndex;
}

int MoreOrEqual::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.setFlag(LF, a.read() >= b.read());
	return pcb->commandIndex;
}

int OpenFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() };
	if (!pcb->file.open(std::string{ filename.read() })) { pcb->state = PCB::processState::waiting; }
	return pcb->commandIndex;
}

int CloseFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() };
	pcb->file.close();
	return pcb->commandIndex;
}

int ReadCharFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() };
	if (pcb->file.isOpen()) {
		std::string result = pcb->file.read(1);
		if (result.size() > 0) {
			pcb->Registers.BX = result[0];
		}
		pcb->Registers.setFlag(LF, true);
	}
	else { pcb->Registers.setFlag(LF, false); }
	return pcb->commandIndex;
}

int ReadCharsFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() }, count{ pcb, pcb->getCommand() }, mem_index{ pcb, pcb->getCommand() };
	if (pcb->file.isOpen()) {
		std::string result = pcb->file.read(count.read());
		if (result.size() > 0) {
			int size = result.size();
			for (int i = 0; i < size; ++i) {
				pcb->writeInDataMemory(mem_index.read() + i, result[i]);
			}
		}
		pcb->Registers.setFlag(LF, true);
	}
	else { pcb->Registers.setFlag(LF, false); }
	return pcb->commandIndex;
}

int WriteCharFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() }, value{ pcb, pcb->getCommand() };
	if (pcb->file.isOpen()) {
		pcb->file.write(std::string{ value.read() });
		pcb->Registers.setFlag(LF, true);
	}
	else { pcb->Registers.setFlag(LF, false); }
	pcb->Registers.BX = pcb->file.getPosition();
	return pcb->commandIndex;
}

int WriteCharsFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() }, count{ pcb, pcb->getCommand() }, mem_index{ pcb, pcb->getCommand() };
	if (pcb->file.isOpen()) {
		int size = count.read(), pos = mem_index.read();
		std::string text = "";
		for (int i = 0; i < size; ++i) {
			text += pcb->readFromDataMemory(pos + i);
		}
		pcb->file.write(text);
		pcb->Registers.BX = pcb->file.getPosition();
		pcb->Registers.setFlag(LF, true);
	}
	else { pcb->Registers.setFlag(LF, false); }
	return pcb->commandIndex;
}

int GetPositionFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() };
	if (pcb->file.isOpen()) {
		pcb->Registers.BX = pcb->file.getPosition();
		pcb->Registers.setFlag(LF, true);
	}
	else { pcb->Registers.setFlag(LF, false); }
	return pcb->commandIndex;
}

int SetPositionFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() }, value{ pcb, pcb->getCommand() };
	if (pcb->file.isOpen()) {
		pcb->file.setPosition(value.read());
		pcb->Registers.setFlag(LF, true);
	}
	else { pcb->Registers.setFlag(LF, false); }
	return pcb->commandIndex;
}

int CreateFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() }, value{ pcb, pcb->getCommand() };
	if (!pcb->file.isFileExist(std::string{ filename.read() })) {
		pcb->Registers.setFlag(LF, pcb->file.createFile(std::string{ filename.read() }));
	}
	else { pcb->Registers.setFlag(LF, false); }
	return pcb->commandIndex;
}

int IsExistFile::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType filename{ pcb, pcb->getCommand() };
	pcb->Registers.setFlag(LF, pcb->file.isFileExist(std::string{ filename.read() }));
	return pcb->commandIndex;
}
