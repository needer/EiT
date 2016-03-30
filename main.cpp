#include "evolutionaryAlgorithm.h"
#include "remoteArduino.h"
#include <windows.h>

int main()
{
	RemoteArduino arduino;
	if (arduino.connect(sf::IpAddress("192.168.4.1"), 10000)) {
		for (int i = 0; i < 10; i++) {
			arduino.send(str);
			Sleep(1000);
		}
	}

	//EvolutionaryAlgorithm ea;
	return 0;
}
