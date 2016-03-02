#include <iostream>
#include "camera.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

// Hewwego!
int main(int argc, char *argv[])
{
	// Init Camera
	Camera c = Camera();
	if (!c.isRunning())
		return 0;

	// Position variables
	Vec2 lastPosition(0, 0);
	Vec2 startPosition(0, 0);
	Vec2 endPosition(0, 0);

	// Clock and Delta Time
	sf::Clock clock;
	sf::Time dt = clock.getElapsedTime();

	// Main Loop
	while (true)
	{
		// Take a picture
		c.capture();

		// Threshold the picture
		c.threshold();

		// Get the position of the object
		Vec2 pos = c.track();

		// Show the target
		c.drawCircle(pos);

		// Calculate velocity
		Vec2 vel = pos - lastPosition;
		lastPosition = pos;


		// Log debug
		std::cout << "Position: " << "(" << pos.x << ", " << pos.y << ")" << std::endl;
		std::cout << "Velocity: " << "(" << vel.x << ", " << vel.y << ")" << std::endl;
		std::cout << "FPS: " << 1.0f / dt.asSeconds() << std::endl;


		// Display 
		c.display();


		// Handle input
		int key = cv::waitKey(1);
		if (key == 27)
			break;
		if (key == 32)
		{
			if (c.state == Camera::NORMAL)
				c.state = Camera::THRESHOLDED;
			else
				c.state = Camera::NORMAL;
		}

		// Calculate delta time
		dt = clock.restart();
	}

	// MAIN PROGRAM
	while (true)
	{
		Vec2 pos = c.track();

		if (cv::waitKey(30) == 27)
			break;
	}


	// EXIT
	return 0;
}
