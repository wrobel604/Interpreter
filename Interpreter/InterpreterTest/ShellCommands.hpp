#pragma once
#include"../Interpreter/Interfaces/AssembleCommandInterface.hpp"

class CreateProcess : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class KillProcess : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class StepProcess : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class StepAllProcess : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class MemoryPrint : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class ChangeMemory : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class RegistersPrint : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class DebugFlag : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class HelpPrint : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class ExitShell : public AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};

