#include "evolutionaryAlgorithm.h"
#include "remoteArduino.h"
#include <string>
#include <windows.h>

int main()
{
	RemoteArduino arduino;
	EvolutionaryAlgorithm ea;
	if (arduino.connect(sf::IpAddress("192.168.4.1"), 10000)) {
	std::cout << "Koblet til" << "\n";
	}
	else {
		return 0;
	}
	std::vector<Individual> pop = ea.children;
	std::cout << pop.size() << "\n";

		for (unsigned i = 0; i < pop.size(); i++) {
			 Individual ind = pop[i];
			 std::cout << "----" << "\n";

			for (unsigned j = 0; j < ind.genotype.size(); j++) {
				arduino.send(ind.genotype[j]);
				std::cout << ind.genotype[j];
				std::cout << "\n";
			}

			Sleep(2000);
		}
	
		Sleep(9000);
	
	return 0;
}
