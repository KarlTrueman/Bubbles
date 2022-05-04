#include <cstring>
#include <iostream>
#include <iostream>
#include <sstream>
#include <thread>
#include<SFML/Network.hpp>
class UDPreceiver
{
public:
	UDPreceiver(sf::UdpSocket& s);
	void recveiver();
private:
	sf::UdpSocket& socket;
};

