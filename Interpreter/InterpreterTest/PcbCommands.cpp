#include "PcbCommands.hpp"
#include"PCB.hpp"
#include"PcbArgumentType.hpp"
#include<iostream>

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
	pcb->Registers.DX = a.read() + b.read();
	return pcb->commandIndex;
}

int Subtraction::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() - b.read();
	return pcb->commandIndex;
}

int Multiplication::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() * b.read();
	return pcb->commandIndex;
}

int Division::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() / b.read();
	return pcb->commandIndex;
}

int Modulo::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() % b.read();
	return pcb->commandIndex;
}

int Decrementation::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() };
	int value = a.read() - 1;
	a.write(value);
	return pcb->commandIndex;
}

int Incrementation::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() };
	int value = a.read() + 1;
	a.write(value);
	return pcb->commandIndex;
}

int And::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() & b.read();
	return pcb->commandIndex;
}

int Or::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() | b.read();
	return pcb->commandIndex;
}

int Xor::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() ^ b.read();
	return pcb->commandIndex;
}

int Not::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() };
	int value = ~a.read();
	a.write(value);
	return pcb->commandIndex;
}

int LeftBitMove::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() << b.read();
	return pcb->commandIndex;
}

int RightBitMove::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(reader);
	PcbArgumentType a{ pcb, pcb->getCommand() }, b{ pcb, pcb->getCommand() };
	pcb->Registers.DX = a.read() >> b.read();
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
