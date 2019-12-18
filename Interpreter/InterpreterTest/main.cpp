#include<iostream>
#include"../Interpreter/Interpreter.hpp"

std::string pr = "SET AX 5\nSET [AX] 65\nOUT [AX]\nEND";

int main(int argc, char** argv) {
	bool debug = false;
	std::shared_ptr<PCB> pcb, p2;
	std::unique_ptr<Interpreter> interpreter;
	if (argc>1) {
		//pcb = PCB::loadProgramFromFile(argv[1]);
		pcb = std::make_shared<PCB>(argv[1]);
	}
	else {
		//pcb = PCB::loadProgramFromFile("out.txt");
		pcb = std::make_shared<PCB>("out.txt");
	}
		pcb->state = processState::active;
	std::cout << "\n";
	debug = argc > 2;
	debug = true; 
	pcb->printMemory(); std::cout << "\n";
	if (pcb!=nullptr && pcb->getMemorySize() > 0) {
		interpreter = std::make_unique<Interpreter>(pcb);
		try {
			while (pcb->state==processState::active) {
				interpreter->pcb->instrucionCounter = (debug)? interpreter->stepWithDebug():interpreter->step();
				//std::cin.get();
				}
		}
		catch (std::exception & e) {
			std::cout << e.what() << "\n";
		}
		
	}
	else {
		std::cout << "No program loaded\n";
	}

	//std::cin.get();
	return 0;
}
