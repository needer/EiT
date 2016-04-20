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
static Vec2 currentPosition = Vec2(0, 0);

float getVirtualScore2(const std::vector<std::string>& data)
{
	sf::Transform transform;

	// Draw
	for (const std::string& s : data)
	{

		if (s == "01")
		{
			transform.rotate(6.25f);
			transform.translate(0.0f, 5.0f);
		}
		if (s == "02")
		{
			transform.rotate(-6.25f);
			transform.translate(0.0f, -5.0f);
		}
		if (s == "10")
		{
			transform.rotate(-6.25f);
			transform.translate(0.0f, 5.0f);
		}
		if (s == "11")
		{
			transform.translate(0.0f, 20.0f);
		}
		if (s == "12")
		{
			transform.rotate(-12.5f);
		}
		if (s == "20")
		{
			transform.rotate(6.25f);
			transform.translate(0.0f, -5.0f);
		}
		if (s == "21")
		{
			transform.rotate(12.5f);
		}
		if (s == "22")
		{
			transform.translate(0.0f, -20.0f);
		}
	}
	sf::Vector2f after = transform.transformPoint(0.0f, 0.0f);

	return sqrtf(powf(after.x, 2.0f) + powf(after.y, 2.0f));
}

int main2()
{
	// Start graphics thread
	Graphics graphics;
	graphics.startThread();
	Sleep(1000);

	// Arduino setup
	EvolutionaryAlgorithm ea;

	int counter = 0;

	bool loop = true;
	while (loop) 
	{

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

			//Calculate score
			double individualScore = (double)getVirtualScore2(ind.genotype);
			std::cout << "Score: " << individualScore;
			
			if (individualScore > 90.0)
			{
				loop = false;
				graphics.saveAsImage("finished");
			}

			counter++;
			graphics.saveAsImage(std::to_string(counter));
			score.push_back(individualScore);
		}



		//Send score to algoritm
		ea.evolutionaryLoop(score);
	}

	// Shutdown the software, wait for threads
	std::cout << "Shutting down..." << std::endl;
	cameraThreadRunning = false;
	graphics.join();
	return 0;
}
