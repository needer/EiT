#include "evolutionaryAlgorithm.h"
#include "remoteArduino.h"
#include <windows.h>

int main()
{
	RemoteArduino arduino;
	EvolutionaryAlgorithm ea;
	if (arduino.connect(sf::IpAddress("192.168.4.1"), 10000)) {
		pop = ea.children;

		for (unsigned i = 0; i < pop.size(); i++) {
			ind = pop[i];

			for (unsigned j = 0; j < ind.size(); i++) {
				arduino.send(ind[i]);
			}
		}
	}

	
	return 0;
}
