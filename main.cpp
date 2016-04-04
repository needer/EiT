#include "evolutionaryAlgorithm.h"
#include "remoteArduino.h"
#include <windows.h>

int main()
{
	RemoteArduino arduino;
	if (arduino.connect(sf::IpAddress("192.168.4.1"), 10000)) {
		
	}

	//EvolutionaryAlgorithm ea;
	return 0;
}
