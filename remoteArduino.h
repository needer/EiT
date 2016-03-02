#pragma once

#include "SFML/Network.hpp"

class RemoteArduino
{
private:
	sf::TcpSocket tcpSocket;
	std::vector<unsigned char> commands;


public:
	RemoteArduino();
	~RemoteArduino();

	bool connect(const sf::IpAddress& ip, unsigned short port);
	void addCommand(int motorNumber, int power);
	void send();
};