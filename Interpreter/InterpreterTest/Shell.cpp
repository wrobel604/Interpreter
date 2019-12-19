#include "Shell.hpp"

Shell::Shell()
{
	endShell = false;
	debug = false;
	interpreter = std::make_unique<Interpreter>();
	pcb = nullptr;
}

Shell::Shell(std::shared_ptr<PCB> process) : Shell()
{
	interpreter->pcb = process;
	interpreter->pcb->state = processState::active;
}

void Shell::getCommand()
{
	command.clear();
	std::string bufor = "";
	std::cout << "> ";
	while (std::cin.peek() != '\n') {
		std::cin >> bufor;
		for (char& c : bufor) { c = std::tolower(c); }
		command.push_back(bufor);
	}
	std::cin.ignore();
}

void Shell::doCommand()
{
	if (command.size() > 0) {
		if (command[0] == "create") {
			if (command.size() > 1) {
				if (interpreter->pcb == nullptr) {
					interpreter->pcb = std::make_shared<PCB>(command[1], command[1] + ".txt");
					interpreter->pcb->state = processState::active;
				}
				else {
					this->pcb = std::make_shared<PCB>(command[1] + ".txt");
					this->pcb->state = processState::ready;
				}
				std::cout << "Zaladowano procesu\n";
			}
			else {
				std::cout << "Nie podano nazwy procesu\n";
			}
			return;
		}

		if (command[0] == "kill") {
			interpreter->pcb = nullptr;
			return;
		}

		if (command[0] == "step") {
			if (interpreter->pcb->state == processState::terminated) { interpreter->pcb = nullptr; }
			else if (interpreter->pcb->state == processState::waiting) {
				std::swap(interpreter->pcb, pcb);
			}
			if (interpreter->pcb == nullptr && pcb == nullptr) {
				std::cout << "Brak procesow w kolejce\n"; return;
			}
			else {
				if (interpreter->pcb == nullptr && pcb != nullptr) {
					interpreter->pcb = pcb; pcb = nullptr;
					interpreter->pcb->state = processState::active;
				}
			}
			std::cout << "Wykonanie procesu  " << interpreter->pcb->getProcessName() << std::endl;
			try {
				if (debug) {
					interpreter->stepWithDebug();
				}
				else {
					interpreter->step();
					std::cout << std::endl;
				}
			}
			catch (std::exception e) {
				std::cout << "Przerwanie dzialania programu: " << e.what() << std::endl;
				interpreter->pcb = nullptr;
			}

			return;
		}
		if (command[0] == "steps") {
			if (interpreter->pcb->state == processState::terminated) { interpreter->pcb = nullptr; }
			else if (interpreter->pcb->state == processState::waiting) {
				std::swap(interpreter->pcb, pcb);
			}
			if (interpreter->pcb == nullptr && pcb == nullptr) {
				std::cout << "Brak procesow w kolejce\n"; return;
			}
			else {
				if (interpreter->pcb == nullptr && pcb != nullptr) {
					interpreter->pcb = pcb; pcb = nullptr;
					interpreter->pcb->state = processState::active;
				}
			}
			std::cout << "Wykonanie procesu  " << interpreter->pcb->getProcessName() << std::endl;
			if (debug) {
				interpreter->stepWithDebug();
			}
			else {
				try {
					while (interpreter->pcb->state == processState::active) {
						interpreter->step();
					}
				}
				catch (std::exception e) {
					std::cout << "Przerwanie dzialania programu: " << e.what() << std::endl;
					interpreter->pcb = nullptr;
				}
				
				std::cout << std::endl;
			}

			return;
		}
		if (command[0] == "memory") {
			if (interpreter->pcb != nullptr) {
				std::cout << "Ilosc przydzielonej pamieci: " << interpreter->pcb->getMemorySize() << std::endl;
				interpreter->pcb->printMemory();
				std::cout << std::endl;
			}
			else {
				std::cout << "Brak procesu z pamiecia\n";
			}
			return;
		}
		if (command[0] == "setnr") {
			if (interpreter->pcb != nullptr) {
				if (command.size() > 2) {
					int id = NumberConversion::stringToInt(command[1]);
					char val = NumberConversion::stringToCharNumber(command[2]);
					interpreter->pcb->writeInDataMemory(id, val);
				}
				else {
					std::cout << "Zbyt mala liczba argumentow\n";
				}
			}
			else {
				std::cout << "Brak procesu z pamiecia\n";
			}
			return;
		}
		if (command[0] == "registers") {
			if (interpreter->pcb != nullptr) {
				std::cout << "\nRegisters:\n\tAX = " << static_cast<int>(interpreter->pcb->getAX()) << "\n\t";
				std::cout << "BX = " << static_cast<int>(interpreter->pcb->getBX()) << "\n\t";
				std::cout << "CX = " << static_cast<int>(interpreter->pcb->getCX()) << "\n\t";
				std::cout << "DX = " << static_cast<int>(interpreter->pcb->getDX()) << "\n";
				std::cout << "Flags:\n\tPF = " << Flags::getFlag(interpreter->pcb->getFlags(), PF) << "\n\t";
				std::cout << "LF = " << Flags::getFlag(interpreter->pcb->getFlags(), LF) << "\n\t";
				std::cout << "SF = " << Flags::getFlag(interpreter->pcb->getFlags(), SF) << "\n\t";
				std::cout << "CF = " << Flags::getFlag(interpreter->pcb->getFlags(), CF) << "\n";
				std::cout << "WF = " << Flags::getFlag(interpreter->pcb->getFlags(), TF) << "\n";
			}
			else {
				std::cout << "Brak procesu z pamiecia\n";
			}
			return;
		}
		if (command[0] == "debug") {
			if (command.size() > 1) {
				if (command[1] == "on") { debug = true; std::cout << "Debugowaanie wlaczone\n"; }
				if (command[1] == "off") { debug = false; std::cout << "Debugowaanie wylaczone\n";
				}
			}
			return;
		}
		if (command[0] == "exit") {
			endShell = true; 
			return;
		}
		if (command[0] == "help") {
			std::cout << "create procesname\ttworzy proces o nazwie 'processname'\n";
			std::cout << "kill\tniszczy aktualnie wykonywany proces\n";
			std::cout << "step\twykonuje instrukcje aktywnego procesu'\n";
			std::cout << "memory\twyswietla zawartosc pamieci aktywnego procesu\n";
			std::cout << "setnr position value\tustawia wartosc komorki position na wartosc value w pamieci aktywnego procesu\n";
			std::cout << "debug on/off\twlacz/wylacz tryb debufowania\n";
			std::cout << "exit\tzakoncz dzialanie programu\n";
			return;
		}
		std::cout << "Nieznane polecenie\n";
	}
}

bool Shell::isEndShell() const
{
	return endShell;
}
