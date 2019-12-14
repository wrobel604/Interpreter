#include "Conversion.hpp"

int NumberConversion::HexToDec(std::string hex)
{
	int size = hex.size();
	int result = 0, bufor = 0;
	for (const char& i : hex) {
		result *= 16;
		if (i >= '0' && i <= '9') { bufor = i - '0'; }
		else
			if (i >= 'A' && i <= 'F') { bufor = i - 'A' + 10; }
			else
				if (i >= 'a' && i <= 'f') { bufor = i - 'a' + 10; }
		result += bufor;
	}
	return result;
}

int NumberConversion::BinToDec(std::string bin)
{
	int size = bin.size();
	int result = 0, two = 1 << (size - 1);
	for (int i = 0; i < size; ++i) {
		if (bin[i] == '1') {
			result += two;
		}
		two >>= 1;
	}
	return result;
}

int NumberConversion::OctToDec(std::string hex)
{
	int size = hex.size();
	int result = 0, bufor = 0;
	for (const char& i : hex) {
		result *= 8;
		if (i >= '0' && i <= '7') { bufor = i - '0'; }
		result += bufor;
	}
	return result;
}

int NumberConversion::stringToInt(std::string number)
{
	if (number.size() > 1 && number[0] == '0') {
		switch (number[1])
		{
		case 'b': return BinToDec(number.substr(2));
		case 'o': return OctToDec(number.substr(2));
		case 'x': return HexToDec(number.substr(2));
		default:
			return atoi(number.c_str());
			break;
		}
	}
	else {
		if (number.size() == 1) {
			if(number[0] >= '0' && number[0] <= '9')return number[0] - '0';
		}
	}
	return atoi(number.c_str());
}

char NumberConversion::stringToCharNumber(std::string number)
{
	return stringToInt(number);
}
