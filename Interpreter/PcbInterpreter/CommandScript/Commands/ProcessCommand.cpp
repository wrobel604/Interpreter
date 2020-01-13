#include "ProcessCommand.hpp"

inline char command::CreateSyncProcess::doCommand(std::shared_ptr<PCB>& pcb, char startArgs) {
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }
	


	return this->ArgumentLength(argv, startArgs, pcb);
}
