#include"ConsoleCommand.hpp"

char command::ConsoleWriteLetter::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::cout << this->getValue(args[0], pcb); 
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::ConsoleWriteNumber::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::cout << static_cast<int>(this->getValue(args[0], pcb));
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::ConsoleWriteWords::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	int size = this->getValue(args[0], pcb);
	int charsPos = this->ArgumentLength(argv, startArgs, pcb);
	args = this->loadArgs(size, charsPos, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	for (int i = 0; i < size; ++i) {
		std::cout << this->getValue(args[i], pcb);
	}
	return startArgs + argv + size;
	return this->ArgumentLength(size, charsPos, pcb);
}
