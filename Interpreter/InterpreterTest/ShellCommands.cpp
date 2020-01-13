#include "ShellCommands.hpp"
#include"Shell.hpp"
#include<iostream>
#include<iomanip>

int CreateProcess::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::string processName = reader->getCommand();
	if (processName != "") {
		if (shell->pcbInterpreter->commandReader == nullptr) {
			if (shell->pcb != nullptr) {
				shell->pcb->state = PCB::processState::active;
				shell->pcbInterpreter->commandReader = std::move(shell->pcb);
				shell->pcb = std::make_shared<PCB>(processName);
				if (shell->pcb == nullptr) {
					std::cout << "Can't create process " << processName << std::endl;
				}
			}
			else {
				std::shared_ptr<PCB> pcb = std::make_shared<PCB>(processName);
				if (pcb != nullptr) {
					pcb->state = PCB::processState::active;
					shell->pcbInterpreter->commandReader = pcb;
				}
				else { std::cout << "Can't create process " << processName << std::endl; }
				
			}
		}
		else {
			if (shell->pcb == nullptr) {
				shell->pcb = std::make_shared<PCB>(processName);
			}
			else {
				std::cout << "No place to create a process";
			}
		}
	}
	else {
		std::cout << "No process name\n";
	}
	return 0;
}

int ExitShell::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	return 1;
}

int KillProcess::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object; 
	if (shell->pcb != nullptr) { shell->pcb->state = PCB::processState::active; }
	shell->pcbInterpreter->commandReader = std::move(shell->pcb);
	return 0;
}

int StepProcess::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	if (shell->pcbInterpreter->commandReader != nullptr) {
		return shell->pcbInterpreter->step();
	}
	else {
		if (shell->pcb != nullptr) {
			shell->pcb->state = PCB::processState::active;
			shell->pcbInterpreter->commandReader = std::move(shell->pcb);
			return shell->pcbInterpreter->step();
		}
		else {
			throw std::exception("No process to do (dummy process should do now)");
		}
	}
	return 0;
}

int StepAllProcess::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	StepProcess step;
	do {
		step.doCommand(reader);
	} while (std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader)->state == PCB::processState::active);
	return 0;
}

int MemoryPrint::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader);
	if (pcb != nullptr) {
		int size = pcb->getMemorySize();
		for (int i = 0; i < size; ++i) {
			std::cout << "|" << pcb->readFromProgramMemory(i) << "|";
		}
	}
	else {
		std::cout << "No active process\n";
	}
	
	return 0;
}

int ChangeMemory::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::string adrr = reader->getCommand();
	std::string val = reader->getCommand();
	char value = 'x';
	int adress = 0;
	//konwersja
	std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader)->writeInDataMemory(adress, value);
	return 0;
}

int RegistersPrint::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader);
	if (pcb != nullptr) {
		std::cout << "AX = " << pcb->Registers.AX << "\n";
		std::cout << "BX = " << pcb->Registers.BX << "\n";
		std::cout << "CX = " << pcb->Registers.CX << "\n";
		std::cout << "DX = " << pcb->Registers.DX << "\n";
		std::cout << "FFFFFFFF" << std::endl;
		char flag = pcb->Registers.Flag;
		for (int i = 0; i < 8; ++i) {
			std::cout << (flag & 1);
			flag >>= 1;
		}
	}
	else {
		std::cout << "No active process\n";
	}
	return 0;
}

int DebugFlag::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::string value = reader->getCommand();
	if (value == "on") { shell->debug = true; } else
	if (value == "off") { shell->debug = true; }
	return 0;
}

int HelpPrint::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::cout <<std::setw(20) << "create processname" <<" - tworzy nowy proces" << std::endl;
	std::cout <<std::setw(20) << "kill" <<" - usuwa aktywny proces" << std::endl;
	std::cout << std::setw(20) << "step" <<" - wykonuje pojedyncza instrukcje aktywnego procesu"  << std::endl;
	std::cout << std::setw(20) << "steps" << " - wykonuje instrukcje aktywnego procesu do jego zakonczenia lub zatrzymania " << std::endl;
	std::cout << std::setw(20) << "memory" <<" - wyswietle zawartosc pamieci aktywnego procesu" << std::endl;
	std::cout << std::setw(20) << "set adress value" <<" - zmienia zawartosc komorki pamieci" << std::endl;
	std::cout << std::setw(20) << "registers" <<" - wyswietla rejestry aktywnego procesu" << std::endl;
	std::cout << std::setw(20) << "debug on/off" <<" - wlacza/wylacza tryb debugowania" << std::endl;
	std::cout << std::setw(20) << "exit" <<" - zamyka konsole" << std::endl;
	return 0;
}
