#include "Interpreter.hpp"

Interpreter::Interpreter() {
	commandFactory = nullptr;
	commandReader = nullptr;
}

int Interpreter::step() {
	std::string command = this->commandReader->getCommand();
	if (this->functionList.find(command) == functionList.end()) {
		if (Interpreter::commandFactory != nullptr) {
			std::unique_ptr<AssembleCommandInterface> commandfunc = commandFactory->getCommand(command);
			if (commandfunc != nullptr) {
				functionList[command] = std::move(commandfunc);
			}
			else {
				std::string message = "No command '" + command + "' in fabric";
				throw std::exception(message.c_str());
			}
		}
		else {
			throw std::exception("Fabric is null");
		}
	}
	commandReader->commandIndex = functionList[command]->doCommand(commandReader);
	return commandReader->commandIndex;
}