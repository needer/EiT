#include "graphics.h"


Graphics::Graphics() : isRunning(false)
{
	
}

void Graphics::startThread()
{
	isRunning = true;
	thread = std::thread(&Graphics::mainLoop, this);
}

void Graphics::mainLoop()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Graph");
	window.setVerticalSyncEnabled(true);

	// run the program as long as the window is open
	while (window.isOpen() && isRunning)
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);



		lock.lock();
		auto dataCopy = data;
		lock.unlock();

		sf::Transform transform;
		transform.translate(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		transform.scale(3.0f, 3.0f);


		// Draw
		for (std::string& s : dataCopy)
		{
			sf::Vector2f before = transform.transformPoint(0.0f, 0.0f);

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
				transform.translate(0.0f, 10.0f);
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
				transform.translate(0.0f, -10.0f);
			}


			sf::Vector2f after = transform.transformPoint(0.0f, 0.0f);

			sf::Vertex line[] =
			{
				sf::Vertex(before),
				sf::Vertex(after)
			};
			window.draw(line, 4, sf::Lines);
		}

		// end the current frame
		window.display();
		screenshotLock.lock();
		screenshot = window.capture();
		screenshotLock.unlock();
	}
}

void Graphics::setData(const std::vector<std::string>& d)
{
	lock.lock();
	data = d;

	lock.unlock();
}

void Graphics::join()
{
	if (isRunning)
	{
		isRunning = false;
		thread.join();
	}
}

void Graphics::saveAsImage(const std::string& name)
{
	screenshotLock.lock();
	
	screenshot.saveToFile("images/" + name + ".png");
	screenshotLock.unlock();
}