#include"ConsoleCommand.hpp"

char command::ConsoleWriteLetter::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::cout << this->getValue(args[0], pcb);
	return startArgs + argv;
}

char command::ConsoleWriteNumber::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	std::cout << static_cast<int>(this->getValue(args[0], pcb));
	return startArgs + argv;
}

char command::ConsoleWriteWords::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	ConsoleWriteLetter write;
	int size = this->getValue(args[0], pcb);
	for (int i = 0; i < size; ++i) {
		write.doCommand(pcb, startArgs + argv + i);
	}
	return startArgs + argv + size;
}
