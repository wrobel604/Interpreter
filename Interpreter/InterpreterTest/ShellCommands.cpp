#include "ShellCommands.hpp"
#include"Shell.hpp"
#include<iostream>
#include<iomanip>
#include<string>
#include"PcbArgumentType.hpp"
#include"NumberConversion.hpp"

int CreateProcess::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::string processName = reader->getCommand();
	if (processName != "") {
		shell->addProcessToQueue(std::make_shared<PCB>(processName));
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
	shell->pcbInterpreter->commandReader = shell->getDummy();
	return 0;
}

int StepProcess::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	if (shell->pcbInterpreter->commandReader == nullptr) { shell->pcbInterpreter->commandReader = shell->getDummy(); }
	if (shell->isDummy()) {
		std::shared_ptr<PCB> pcb = shell->removeProcessFromQueue();
		if (pcb != nullptr) {
			pcb->state = PCB::processState::active;
			shell->pcbInterpreter->commandReader = std::move(pcb);
		}
	}
	int start = shell->pcbInterpreter->commandReader->commandIndex;
	int end = shell->pcbInterpreter->step();
	if (shell->debug) {
		shell->pcbInterpreter->commandReader->commandIndex = start;
		std::string command = shell->pcbInterpreter->commandReader->getCommand();
		std::cout << "\nCommand: " << command << std::endl <<"Arguments: ";
		if (command == "JMP" || command == "JMZ") {
			std::cout<< shell->pcbInterpreter->commandReader->getCommand() <<std::endl;
		}
		else {
			while (shell->pcbInterpreter->commandReader->commandIndex < end) {
				std::cout << shell->pcbInterpreter->commandReader->getCommand() << " ";
			}
			std::cout << std::endl;
		}
		RegistersPrint r; r.doCommand(reader);
		shell->pcbInterpreter->commandReader->commandIndex = end;
	}
	std::shared_ptr<PCB> pcb = std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader);
	if (pcb->state != PCB::processState::active) { 
		if (pcb->state == PCB::processState::waiting) { shell->addProcessToQueue(pcb);}
		shell->pcbInterpreter->commandReader = nullptr; 
	}
	return 0;
}

int StepAllProcess::doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader)
{
	std::shared_ptr<ConsoleCommandCreator> ccc = std::dynamic_pointer_cast<ConsoleCommandCreator>(reader);
	Shell* shell = (Shell*)ccc->object;
	std::string countArg = ccc->getCommand();
	int count = 0;
	StepProcess step;
	if (countArg != "") {
		count = NumberConversion::stringToInt(countArg);
		while(count-->0 && shell->pcbInterpreter->commandReader != nullptr && std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader)->state == PCB::processState::active){
			step.doCommand(reader);
		}
	}
	else {
		do {
			step.doCommand(reader);
		} while (shell->pcbInterpreter->commandReader != nullptr && std::dynamic_pointer_cast<PCB>(shell->pcbInterpreter->commandReader)->state == PCB::processState::active);
	}
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
		std::cout << "Instruction counter: " << pcb->commandIndex << std::endl;
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
	if (value == "off") { shell->debug = false; }
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
