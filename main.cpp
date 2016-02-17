#include <iostream>
#include "camera.h"
#include "SFML/Window.hpp"

int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;
	sf::Window w;
	while (w.isOpen())
	{
		sf::Event e;
		w.pollEvent(e);
	}

	return 0;
}
