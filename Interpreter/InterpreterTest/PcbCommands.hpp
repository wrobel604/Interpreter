#pragma once
#include"../Interpreter/Interfaces/AssembleCommandInterface.hpp"

class ConsoleWriteLetter : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class ConsoleWriteNumber : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class SetValue : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class EndProgram : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
//Matematyka
class Addition : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Subtraction : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Multiplication : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Division : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Modulo : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Incrementation : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Decrementation : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Not : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class And : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Or : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Xor : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class LeftBitMove : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class RightBitMove : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Equal : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class Less : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class More : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class LessOrEqual : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class MoreOrEqual : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class JumpIfTrue : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class JumpIfFalse : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class CreateFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class OpenFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class CloseFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class ReadCharFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class ReadCharsFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class WriteCharFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class WriteCharsFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class GetPositionFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class SetPositionFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};
class IsExistFile : public AssembleCommandInterface {
public:

	// Inherited via AssembleCommandInterface
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) override;
};