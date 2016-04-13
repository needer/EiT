#include "evolutionaryAlgorithm.h"
#include "remoteArduino.h"
#include "camera.h"
#include <string>
#include <windows.h>
#include <thread>
#include <mutex>


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
	// Start camera thread
	std::thread cThread (cameraThread);

	// Wait for input to continue
	std::cout << "Please configure your camera settings correctly!" << std::endl;
	std::cout << "Type anything to continue the program: ";
	int cont = 0;
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
		std::cout << "Koblet til" << "\n";
	else
	{
		cameraThreadRunning = false;
		cThread.join();
		return 0;
	}

	while (true) {
		// Print population
		std::vector<Individual> pop = ea.children;
		std::cout << pop.size() << "\n";

		//Vecotr of scores
		std::vector<double> score;

		// For each population
		for (unsigned i = 0; i < pop.size(); i++)
		{
			Individual ind = pop[i];
			std::cout << "----" << "\n";

			//Get stop position from camera
			posMutex.lock();

			double startPos = (double)currentPosition.magnitude();

			posMutex.unlock();

			// For each individual
			for (unsigned j = 0; j < ind.genotype.size(); j++)
			{
				arduino.send(ind.genotype[j]);
				std::cout << ind.genotype[j];
				std::cout << "\n";
			}

			//Get stop position from camera
			posMutex.lock();

			double stopPos = (double)currentPosition.magnitude();

			posMutex.unlock();

			//Calculate score
			double individualScore = stopPos - startPos;

			/*std::string in = "";
			double individualScore = 0.0;

			std::cin >> in;
			individualScore = std::stod(in);*/

			score.push_back(individualScore);

			Sleep(2000);
		}

		//Send score to algoritm
		ea.evolutionaryLoop(score);

		Sleep(9000);
	}

	// Shutdown the other thread
	cameraThreadRunning = false;
	cThread.join();

	return 0;
}
