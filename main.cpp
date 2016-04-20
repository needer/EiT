#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include "evolutionaryAlgorithm.h"
#include "remoteArduino.h"
#include "camera.h"
#include "graphics.h"


static bool cameraThreadRunning = true;
static std::mutex posMutex;
static Vec2 currentPosition = Vec2(0,0);

void cameraThread()
{
	// Camera setup
	Camera c = Camera();
	
	// Variables
	Vec2 lastPosition(0, 0);
	Vec2 startPosition(0, 0);
	Vec2 endPosition(0, 0);

	// Clock and Delta Time
	sf::Clock clock;
	sf::Time dt = clock.getElapsedTime();

	while (cameraThreadRunning)
	{
		// Take a picture
		c.capture();

		// Threshold the picture
		c.threshold();

		// Get the position of the object
		Vec2 pos = c.track();
		posMutex.lock();
		currentPosition = pos;
		posMutex.unlock();

		// Draw the target on the screen
		c.drawCircle(pos);

		// Calculate velocity
		Vec2 vel = pos - lastPosition;
		lastPosition = pos;

		// Display on screen
		c.display();

		// Handle input
		int key = cv::waitKey(1);
		if (key == 27)
			break;
		if (key == 32)
		if (c.state == Camera::NORMAL)
			c.state = Camera::THRESHOLDED;
		else
			c.state = Camera::NORMAL;

	}

}

int main()
{
	// Start graphics thread
	Graphics graphics;
	graphics.startThread();
	std::vector<std::string> aaaa;
	graphics.setData(aaaa);
	// Start camera thread
	std::thread cThread (cameraThread);

	// Wait for input to continue
	std::cout << "Please configure your camera settings correctly!" << std::endl;
	std::cout << "Type anything to continue the program: ";
	int cont;
	std::cin >> cont;
	std::cout << "Main thread started" << std::endl;


	// Clock and Delta Time
	sf::Clock clock;
	sf::Time dt = clock.getElapsedTime();

	// Arduino setup
	RemoteArduino arduino;
	EvolutionaryAlgorithm ea;

	
	// Connect to arduiono
	if (arduino.connect(sf::IpAddress("192.168.4.1"), 10000))
		std::cout << "Koblet til" << std::endl;
	else
	{
		cameraThreadRunning = false;
		cThread.join();
		graphics.join();
		return 0;
	}

	std::cout << "Sender 10";
	arduino.send("10");
	
	//Stop
	arduino.send("00");

	while (false) {
		// Print population
		std::vector<Individual> pop = ea.children;
		std::cout << pop.size() << std::endl;

		//Vecotr of scores
		std::vector<double> score;

		// For each population
		for (unsigned i = 0; i < pop.size(); i++)
		{
			Individual ind = pop[i];
			std::cout << "----" << "\n";

			//Get stop position from camera
			posMutex.lock();

			Vec2 startPos = currentPosition;

			posMutex.unlock();

			graphics.setData(ind.genotype);

			// For each individual
			for (unsigned j = 0; j < ind.genotype.size(); j++)
			{
				arduino.send(ind.genotype[j]);
				std::cout << ind.genotype[j];
				std::cout << "\n";

				//Geting curen position
				posMutex.lock();

				Vec2 pos = currentPosition;

				posMutex.unlock();

				//std::cout << pos.x << " " << pos.y << std::endl;

				//Checing if the rotbot has left the area
				if (pos.x == -1 && pos.y == -1) {
					// Pause for a second
					arduino.send("00");
					std::cout << "The robot has left the area" << std::endl;
					std::cout << "Continue?" << std::endl;
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					int cunt;
					std::cin >> cunt;

					arduino.send(ind.genotype[j]);
					std::cout << ind.genotype[j];
					std::cout << "\n";
				}

			}
			arduino.send("00");
			//Get stop position from camera
			posMutex.lock();

			Vec2 stopPos = currentPosition;

			posMutex.unlock();

			//Calculate score
			double individualScore = (double)(stopPos - startPos).magnitude();
			std::cout << "Score: " << individualScore;
			/*std::string in = "";
			double individualScore = 0.0;

			std::cin >> in;
			individualScore = std::stod(in);*/

			score.push_back(individualScore);

			//Sleep(2000);
		}


		//Send score to algoritm
		ea.evolutionaryLoop(score);

		// Pause for a second
		/*std::cout << "Continue?" << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		int cunt;
		std::cin >> cunt;*/
	}

	// Shutdown the other thread
	std::cout << "Shutting down..." << std::endl;
	std::cout << "Shutting down.." << std::endl;
	std::cout << "Shutting down." << std::endl;
	cameraThreadRunning = false;
	cThread.join();
	graphics.join();
	
	return 0;
}
