#include <iostream>
#include "camera.h"
#include "SFML/Window.hpp"

// Hewwego!
int main(int argc, char *argv[])
{
	// INIT
	Camera c = Camera();
	if (!c.isRunning())
		return 0;


	// CALIBRATION
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

		// Display current position in console
		std::cout << "(" << pos.x << ", " << pos.y << ")" << std::endl;


		// Display 
		c.display();


		// Handle input
		int key = cv::waitKey(10);
		if (key == 27)
			break;
		if (key == 32)
		{
			if (c.state == Camera::NORMAL)
				c.state = Camera::THRESHOLDED;
			else
				c.state = Camera::NORMAL;
		}
		
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
