#pragma once
#include<string>
#include<memory>
#include"AssembleCommandInterface.hpp"

class AssembleCommandFactoryInterface {
public:
	virtual std::unique_ptr<AssembleCommandInterface> getCommand(std::string commandname) = 0;
};