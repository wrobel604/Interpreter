#pragma once
#include<string>
#include<regex>

class Conversion {
public:
	enum class ValueType : char{
		Register,
		Flag,
		MemoryAdress,
		Number,
		Other
	};
	static char string_to_charNumber(std::string numbers) {
		return std::atoi(numbers.c_str());
	}
	static char getMemoryAdress(std::string addr) {
		std::regex regex{ "^\\[([0-9]+)\\]$" };
		std::smatch match;
		if (std::regex_search(addr, match, regex)) {
			return Conversion::string_to_charNumber(match[1]);
		}
		return 0;
	}
	static ValueType getCommandType(std::string arg, char& outValue) {
		std::regex regex{ "^\\[([0-9]+)\\]$" };
		std::smatch match;
		if (std::regex_search(arg, match, regex)) {
			outValue = string_to_charNumber(match[1]);
			return ValueType::MemoryAdress;
		}
		regex = std::regex{ "^([0-9]+)$" };
		if (std::regex_search(arg, match, regex)) {
			outValue = string_to_charNumber(match[1]);
			return ValueType::Number;
		}
		regex = std::regex{ "^([A-Z]X)$" };
		if (std::regex_search(arg, match, regex)) {
			arg = match[1];
			outValue = arg[0];
			return ValueType::Register;
		}
		regex = std::regex{ "^([A-Z]F)$" };
		if (std::regex_search(arg, match, regex)) {
			arg = match[1];
			outValue = arg[0];
			return ValueType::Flag;
		}
	}
};