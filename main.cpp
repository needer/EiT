#include <iostream>
#include "camera.h"
#include "SFML/Audio.hpp"

int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;
	Camera c;

	sf::Music m;
	m.openFromFile("C:/asdf.mp3");

	return 0;
}
