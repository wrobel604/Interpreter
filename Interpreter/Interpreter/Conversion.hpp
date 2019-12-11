#pragma once
#include<string>
#include<regex>

namespace {
	int HexToDec(std::string& hex) {
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
	int BinToDec(std::string& bin) {
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

	int OctToDec(std::string& hex) {
		int size = hex.size();
		int result = 0, bufor = 0;
		for (const char& i : hex) {
			result *= 8;
			if (i >= '0' && i <= '7') { bufor = i - '0'; }
			result += bufor;
		}
		return result;
	}
}

class Conversion {
public:
	static char string_to_charNumber(std::string numbers) {
		return std::atoi(numbers.c_str());
	}
};