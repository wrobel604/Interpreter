#pragma once
#include"../Interpreter/Interfaces/AssembleCommandInterface.hpp"

class ConsoleWriteLetter : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};