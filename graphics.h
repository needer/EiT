#pragma once

#include "SFML/Graphics.hpp"
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <iostream>

class Graphics
{
private:
	sf::RenderWindow window;
	bool isRunning;
	void mainLoop();
	std::thread thread;
	std::mutex lock;
	std::vector<std::string> data;

	std::mutex screenshotLock;
	sf::Image screenshot;
public:
	Graphics();
	void startThread();
	void setData(const std::vector<std::string>& d);
	void join();
	void Graphics::saveAsImage(const std::string& namePath);
};
