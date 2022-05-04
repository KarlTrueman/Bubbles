#include "UDPreceiver.h"
#define BUFF_SIZE 1024

UDPreceiver::UDPreceiver(sf::UdpSocket& s) : Usocket(s)
{
}

void UDPreceiver::receive()
{
	while (true)
	{
		sf::IpAddress recipient;
		unsigned short remote_port;
		char data[BUFF_SIZE];
		std::size_t received;
		std::memset(data, 0, BUFF_SIZE);
		if (Usocket.receive(data, BUFF_SIZE, received, recipient, remote_port) != sf::Socket::Done)
		{
			std::cerr << "Big issue receiving" << std::endl;
			exit(0);
		}

		std::string s = std::string(data);
		sf::Socket::Status status = Usocket.send(s.c_str(), s.length(), recipient, remote_port);
		if (status != sf::Socket::Done)
		{
			std::cerr << "Big issue sending" << std::endl;
			exit(0);
		}

	}
}