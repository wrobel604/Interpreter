#include<iostream>
#include<Interpreter.hpp>

std::string pr = "SET AX 5\nSET [AX] 65\nOUT [AX]\nEND";

int main(int argc, char** argv) {
	bool debug = false;
	std::shared_ptr<PCB> pcb;
	//for (int i = 0; i < argc; ++i) { std::cout<<"|" << argv[i] << "|\t"; }std::cout << "\n";
	if (argc > 1) {
		pcb = std::make_unique<PCB>(PCB::loadProgramFromFile(argv[1]));
		if (argc > 2) { debug = true; std::cout << "Tryb debugowania: " << debug << "\n";}
		Interpreter interpreter{ pcb };
		int steps = 0;
		try {
			while (steps != interpreter.getPCB()->program->size()) {
				steps = interpreter.step(steps, debug);
			}
		}
		catch (std::exception & e) {
			std::cout << "|\nProgram end with error: " << e.what() << "\n";
		}
	}
	else {
		std::cout << "No program to load\n";
	}
	
	//std::cin.get();
	return 0;
}