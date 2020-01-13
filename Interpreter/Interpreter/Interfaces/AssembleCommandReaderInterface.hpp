#pragma once
#include<vector>
#include<string>

class AssembleCommandReaderInterface {
public:
	int commandIndex = 0;
	virtual std::string getCommand() = 0;
};