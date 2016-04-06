#include "evolutionaryAlgorithm.h"
#include "remoteArduino.h"
#include <string>
#include <windows.h>

int main()
{
	RemoteArduino arduino;
	EvolutionaryAlgorithm ea;
	if (arduino.connect(sf::IpAddress("192.168.4.1"), 10000)) {
		std::vector<Individual> pop = ea.children;

		for (unsigned i = 0; i < pop.size(); i++) {
			 Individual ind = pop[i];

			for (unsigned j = 0; j < ind.genotype.size(); j++) {
				arduino.send(ind.genotype[j]);
			std::cout << "test";
			}
		}
	}

	
	return 0;
}
