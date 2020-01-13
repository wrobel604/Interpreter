#include "FileCommand.hpp"

char command::OpenFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::string filename = std::string{ getValue(args[0], pcb) };
	if (pcb->fileName.empty()) {
		std::ifstream file(filename);
		if (file.is_open()) { pcb->fileName = filename;
		//std::cout << "|OPEN|";
		}else{ //std::cout << "|NO_OPEN|"; 
		}

		file.close();
	}
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::CloseFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::string filename = std::string{ getValue(args[0], pcb) };
	if (pcb->fileName == filename) { 
		pcb->fileName.clear();
		//std::cout << "|CLOSE|";
	}
	else {
		//std::cout << "|NO_CLOSE|";
	}
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::ReadCharFromFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::string filename = std::string{ getValue(args[0], pcb) };
	if (pcb->fileName == filename) { 
		std::ifstream in(filename);
		if (in.is_open()) {

		char sign;
		in.seekg(getValue(args[1], pcb));
		if (in.read(&sign, 1)) { pcb->setBX(sign); }
		//std::cout << "|READ|";
		}else{ //std::cout << "|NO_READ|"; 
		}
	}
	else {
		//std::cout << "|NO_READ|";
	}
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::WriteCharToFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 3;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::string filename = std::string{ getValue(args[0], pcb) };
	if (pcb->fileName == filename) {
		std::ofstream out(filename);
		if (out.is_open()) {
			char sign = getValue(args[2], pcb);
			out.seekp(getValue(args[1], pcb));
			out.write(&sign, 1);
			//std::cout << "|WRITE|";
		}else{ //std::cout << "|NO_WRITE|"; 
		}
	}
	else {
		//std::cout << "|NO_WRITE|";
	}
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::CreateFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::string filename = std::string{ getValue(args[0], pcb) };
	std::ofstream file(filename, std::fstream::out);
	if (file.is_open()) {
		//std::cout << "|Create|";
		file.close();
	}
	else {
		//std::cout << "|NO_create|";
	}
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::SetPosition::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	return 0;
}

char command::GetPosition::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	return 0;
}

char command::AppendCharToFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::string filename = std::string{ getValue(args[0], pcb) };
	if (pcb->fileName == filename) {
		std::ofstream out(filename, std::fstream::app);
		if (out.is_open()) {
			char sign = getValue(args[1], pcb);
			out << sign;
			//std::cout << "|APP|";
		}
		else { //std::cout << "|NO_APP|"; 
		}
	}
	else {
		//std::cout << "|NO_APP|";
	}
	return this->ArgumentLength(argv, startArgs, pcb);
}
