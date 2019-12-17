#pragma once

#define PF 1
#define LF 1<<1
#define SF 1<<2
#define CF 1<<3
#define TF 1<<4

class Flags {
public:
	static bool getFlag(char flags, char index){
		return (flags & index) == index;
	}
	static char setFlag(char flags, char index, bool value) {
		if (value) {
			flags |= index;
		}
		else {
			flags &= (~index);
		}
		return flags;
	}
	static char setFlags(char flags, int valueResult) {
		flags = Flags::setFlag(flags, PF, (valueResult & 1) == 0);
		flags = Flags::setFlag(flags, LF, valueResult != 0);
		flags = Flags::setFlag(flags, SF, (valueResult < 0));
		flags = Flags::setFlag(flags, CF, (valueResult > 128));
		return flags;
	}
};