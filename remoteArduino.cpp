#include <iostream>
#include "remoteArduino.h"

RemoteArduino::RemoteArduino() :
tcpSocket(), commands()
{

}

RemoteArduino::~RemoteArduino()
{
	tcpSocket.disconnect();
}

bool RemoteArduino::connect(const sf::IpAddress& ip, unsigned short port)
{
	tcpSocket.disconnect();
	
	sf::Socket::Status status = tcpSocket.connect(ip, port);
	if (status != sf::Socket::Done)
		return false;
	return true;
}

void RemoteArduino::addCommand(int motorNumber, int power)
{
	unsigned char motor = (unsigned char)motorNumber;
	unsigned char poww = (unsigned char)power;
	commands.push_back(motor);
	commands.push_back(poww);
}

void RemoteArduino::sendSequence(std::vector<std::string> sequence)
{
	for (unsigned i = 0; i < sequence.size(); i++) {
		std::string message = sequence[i];
		tcpSocket.send(message.c_str(), message.length());

		Sleep(1000);
	}

	/*tcpSocket.send(message.c_str(), message.length());
	commands.clear();*/
}
