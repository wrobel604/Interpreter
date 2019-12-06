#include<iostream>
#include<Interpreter.hpp>


int main(int argc, char** argv) {
	bool debug = false;
	std::shared_ptr<PCB> pcb;
	std::unique_ptr<Interpreter> interpreter;
	if (argc>1) {
		pcb = std::make_shared<PCB>(argv[1]);
	}
	else {
		pcb = std::make_shared<PCB>("out.txt");
	}
	for (std::string s : *pcb->program) { std::cout << s << " "; }std::cout << "\n";
	debug = argc > 2;
	//debug = true;
	if (pcb!=nullptr && pcb->program->size() > 0) {
		interpreter = std::make_unique<Interpreter>(pcb);
		int step = 0;
		pcb->writeInMemory(10, 70);
		try {
			while (pcb->status) {
				step = (debug)? interpreter->stepWithDebug(step):interpreter->step(step);
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