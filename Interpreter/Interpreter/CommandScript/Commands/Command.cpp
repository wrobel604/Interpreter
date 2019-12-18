#include"Command.hpp"

char command::SetValue::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 2;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	if (args[0].getType() != ArgumentType::Type::Value && args[0].getType() != ArgumentType::Type::Unknown) {
		this->setValue(args[0], this->getValue(args[1], pcb), pcb);
	}
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::JumpIfNotZero::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	return (Flags::getFlag(pcb->getFlags(), LF)) ? this->getValue(args[0], pcb) : this->ArgumentLength(argv, startArgs, pcb);;
}

char command::JumpIfZero::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	return (!Flags::getFlag(pcb->getFlags(), LF)) ? this->getValue(args[0], pcb) : this->ArgumentLength(argv, startArgs, pcb);;
}

char command::IF::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	pcb->setFlags(Flags::setFlag(pcb->getFlags(), LF, this->getValue(args[0], pcb)));
	return this->ArgumentLength(argv, startArgs, pcb);
}

char command::End::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	pcb->state = processState::terminated;
	if (pcb->parent != nullptr && Flags::getFlag(pcb->getFlags(), TF)) {
		pcb->parent->state = processState::ready;
	}
	return startArgs;
}
