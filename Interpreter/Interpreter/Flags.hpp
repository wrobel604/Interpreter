#pragma once

#define PF 1
#define LF 1<<1
#define SF 1<<2
#define CF 1<<3

class Flags {
	char flags;
public:
	Flags() {
		flags = 0;
	}
	
	bool getFlag(char index) const {
		return (flags & index) == index;
	}
	void setFlag(char index, bool value) {
		if (value) {
			flags |= index;
		}
		else {
			flags &= (~index);
		}
	}

	const char getFlags() const {
		return flags;
	}
	bool operator[](char index) {
		return getFlag(index);
	}
	Flags& operator=(char value) {
		flags = value;
	}
	Flags& operator=(const Flags& value) {
		flags = value.flags;
	}

	static void setFlags(Flags& flags, int valueResult) {
		flags.setFlag(PF, valueResult & 1);
		flags.setFlag(LF, valueResult != 0);
		flags.setFlag(SF, (valueResult<0));
		flags.setFlag(CF, (valueResult>255));
	}
};