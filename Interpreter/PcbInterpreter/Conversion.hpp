#pragma once
#include<string>
#include<regex>

namespace NumberConversion{
	int HexToDec(std::string hex);
	int BinToDec(std::string bin);
	int OctToDec(std::string hex);

	int stringToInt(std::string number);
	char stringToCharNumber(std::string number);
}