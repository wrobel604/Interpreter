#include "AssemblerTranslator.hpp"

int AssemblerTranslator::ArgumentLength(int argc, int startPos, std::shared_ptr<PCB>& pcb)
{
	for (int i = 0; i < argc; ++i) {
		startPos += AssembleCommandInterface::loadWordFromPcb(startPos, pcb).size() + 1;
	}
	return startPos;
}
