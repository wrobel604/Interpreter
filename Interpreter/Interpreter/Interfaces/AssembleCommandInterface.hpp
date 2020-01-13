#pragma once
#include"AssembleCommandReaderInterface.hpp"
#include<memory>

class AssembleCommandInterface {
public:
	virtual int doCommand(std::shared_ptr<AssembleCommandReaderInterface>& reader) = 0;
};