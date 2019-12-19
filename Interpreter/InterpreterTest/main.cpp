#include<iostream>
#include"Shell.hpp"



int main(int argc, char** argv) {
	std::unique_ptr<Shell> shell = nullptr;
	if (argc > 1) {
		shell = std::make_unique<Shell>(std::make_shared<PCB>(argv[1]));
	}
	else {
		shell = std::make_unique<Shell>();
	}
	

	do {
		shell->getCommand();
		shell->doCommand();
	} while (!shell->isEndShell());

	//std::cin.get();
	return 0;
}
