#include "ShellCommands.hpp"
#include"Shell.hpp"
#include<iostream>
#include<iomanip>
#include<string>
#include"PcbArgumentType.hpp"

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
	int start, end;
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	if (shell->pcbInterpreter->commandReader != nullptr) {
		start = shell->pcbInterpreter->commandReader->commandIndex;
		end = shell->pcbInterpreter->step();
	}
	else {
		if (shell->pcb != nullptr) {
			shell->pcb->state = PCB::processState::active;
			shell->pcbInterpreter->commandReader = std::move(shell->pcb);
			start = shell->pcbInterpreter->commandReader->commandIndex;
			end = shell->pcbInterpreter->step();
		}
		else {
			throw std::exception("No process to do (dummy process should do now)");
		}
	}
	if (shell->debug) {
		shell->pcbInterpreter->commandReader->commandIndex = start;
		std::cout << std::endl <<"Command: " << shell->pcbInterpreter->commandReader->getCommand() <<std::endl <<"Arguments: ";
		while (shell->pcbInterpreter->commandReader->commandIndex < end) {
			std::cout << shell->pcbInterpreter->commandReader->getCommand() <<" ";
		}
		std::cout<<std::endl;
		RegistersPrint r; r.doCommand(reader);
	}
	if (shell->pcbInterpreter->commandReader != nullptr) {
		std::shared_ptr<AssembleCommandReaderInterface> waitpcb;
		switch (std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader)->state)
		{
		case PCB::processState::terminated:shell->pcbInterpreter->commandReader = std::move(shell->pcb); break;
		case PCB::processState::waiting:
			waitpcb = shell->pcbInterpreter->commandReader;
			shell->pcbInterpreter->commandReader = std::move(shell->pcb);
			shell->pcb = std::dynamic_pointer_cast<PCB>(waitpcb);
			break;
		default:
			break;
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
	} while (shell->pcbInterpreter->commandReader != nullptr && std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader)->state == PCB::processState::active);
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
	if (shell->pcbInterpreter->commandReader == nullptr) { throw std::exception{"No active process in memory"}; }
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader);
	char value = PcbArgumentType{ pcb, val }.read();
	int adress = std::atoi(adrr.c_str());
	std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader)->writeInDataMemory(adress, value);
	return 0;
}

int RegistersPrint::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader);
	if (pcb != nullptr) {
		std::cout << "AX = " << (int)pcb->Registers.AX <<"(" << pcb->Registers.AX << ")\n";
		std::cout << "BX = " << (int)pcb->Registers.BX << "(" << pcb->Registers.BX << ")\n";
		std::cout << "CX = " << (int)pcb->Registers.CX << "(" << pcb->Registers.CX << ")\n";
		std::cout << "DX = " << (int)pcb->Registers.DX << "(" << pcb->Registers.DX << ")\n";
		std::cout << "PLSCZ---" << std::endl;
		char flag = pcb->Registers.Flag;
		for (int i = 0; i < 8; ++i) {
			std::cout << (flag & 1);
			flag >>= 1;
		}
		std::cout << std::endl;
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
	std::cout << std::setw(20) << "pos" << " -  wyswietla polozenie instrukcji" << std::endl;
	std::cout << std::setw(20) << "memory" <<" - wyswietle zawartosc pamieci aktywnego procesu" << std::endl;
	std::cout << std::setw(20) << "set adress value" <<" - zmienia zawartosc komorki pamieci" << std::endl;
	std::cout << std::setw(20) << "registers" <<" - wyswietla rejestry aktywnego procesu" << std::endl;
	std::cout << std::setw(20) << "debug on/off" <<" - wlacza/wylacza tryb debugowania" << std::endl;
	std::cout << std::setw(20) << "exit" <<" - zamyka konsole" << std::endl;
	std::cout << std::setw(20) << "file" <<" - operuje na plikach. Wpisz aby uzyskac pomoc." << std::endl;
	return 0;
}

int StepIndex::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	if (shell->pcbInterpreter->commandReader == nullptr) { throw std::exception{"No active process"}; }
	std::cout << shell->pcbInterpreter->commandReader->commandIndex <<std::endl;
	return 0;
}

int FileCommander::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::string command = ccc->getCommand(), adress = ccc->getCommand();
	if (command == "") { throw std::exception{ "file command isn't complete\nCorrectly command:\nfile create file_adress\nfile read file_adress size\nfile write file_adress text\nfile append file_adress text\n" }; }
	if(command=="create"){
		if (FileManager::createFile(adress)) {
			std::cout << "Utworzono plik " << adress << std::endl;
		}else{
			std::cout << "Plik " << adress <<" juz istnieje" << std::endl;
		}
	}
	if (!FileManager::isFileExist(adress)) { throw std::exception{ "File doesn't exist" }; }
	FileManager file;
	if (file.open(adress)) {
		if (command == "read") { read(reader, file); }else
		if (command == "write") { write(reader, file);}else
		if (command == "size") { size(file); }
		if (command == "append") { append(reader, file); }
		file.close();
	}
	else {
		throw std::exception{ std::string{"Cannot open file "+adress}.c_str() };
	}
	return 0;
}

void FileCommander::read(std::shared_ptr<AssembleCommandReaderInterface>& reader, FileManager& file)
{
	int count = std::atoi(reader->getCommand().c_str());
	std::cout << file.read(count) << std::endl;
}

void FileCommander::write(std::shared_ptr<AssembleCommandReaderInterface>& reader, FileManager& file)
{
	std::string value;
	int char_counter = 0;
	while((value = reader->getCommand())!="") {
		if (char_counter != 0) { file.write(" "); }
		file.write(value);
		char_counter += value.size();
	}
	std::cout << "Zapisano " << char_counter << " bajtow" << std::endl;
}

void FileCommander::size(FileManager& file)
{
	std::cout << file.getFileSize() << std::endl;
}

void FileCommander::append(std::shared_ptr<AssembleCommandReaderInterface>& reader, FileManager& file)
{
	file.setPosition(file.getFileSize());
	write(reader, file);
}
