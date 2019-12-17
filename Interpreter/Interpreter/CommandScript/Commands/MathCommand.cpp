#include"MathCommand.hpp"

char command::Addition::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) + this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}

char command::Subtraction::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) - this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}

char command::Multiplication::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) * this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}

char command::Division::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	if (this->getValue(args[1], pcb) != 0) {
		int result = this->getValue(args[0], pcb) / this->getValue(args[1], pcb);
		pcb->setDX(result);
		pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	}
	else { throw std::exception("Divided by 0"); }

	return startArgs + argv;
}

char command::Modulo::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	if (this->getValue(args[1], pcb) != 0) {
		int result = this->getValue(args[0], pcb) % this->getValue(args[1], pcb);
		pcb->setDX(result);
		pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	}
	else { throw std::exception("Divided by 0"); }
	return startArgs + argv;
}

char command::Incrementation::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }

	this->setValue(args[0], this->getValue(args[0], pcb) + 1, pcb);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), this->getValue(args[0], pcb)));

	return startArgs + argv;
}

char command::Decrementation::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }

	this->setValue(args[0], this->getValue(args[0], pcb) - 1, pcb);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), this->getValue(args[0], pcb)));

	return startArgs + argv;
}

char command::And::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) & this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}

char command::Or::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) | this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}

char command::Xor::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) ^ this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}

char command::Not::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	pcb->setDX(~this->getValue(args[0], pcb));
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), this->getValue(args[0], pcb)));
	return startArgs + argv;
}

char command::MLF::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) << this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}

char command::MRT::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	int result = this->getValue(args[0], pcb) >> this->getValue(args[1], pcb);
	pcb->setDX(result);
	pcb->setFlags(Flags::setFlags(pcb->getFlags(), result));
	return startArgs + argv;
}
