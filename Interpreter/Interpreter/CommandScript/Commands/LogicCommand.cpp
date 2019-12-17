#include "LogicCommand.hpp"

char command::Equal::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	bool result = (this->getValue(args[0], pcb) == this->getValue(args[1], pcb));
	//std::cout <<"|" << result << "|\n";
	pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
	return startArgs + argv;
}

char command::Less::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	bool result = (this->getValue(args[0], pcb) < this->getValue(args[1], pcb));
	pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
	return startArgs + argv;
}

char command::More::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	bool result = (this->getValue(args[0], pcb) > this->getValue(args[1], pcb));
	pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
	return startArgs + argv;
}

char command::MoreOrEqual::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	bool result = (this->getValue(args[0], pcb) >= this->getValue(args[1], pcb));
	pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
	return startArgs + argv;
}

char command::LessOrEqual::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	bool result = (this->getValue(args[0], pcb) <= this->getValue(args[1], pcb));
	pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, result));
	return startArgs + argv;
}
