#include <SFML/Network.hpp>
#include <functional>
#include "Player.h"
#include "Grid.h"
#include "bubble.h"

#define PORT 4300

void net_run(std::function<sf::Socket::Status(void)> f, std::string error_message);
using message = std::pair<sf::TcpSocket*, sf::Packet>;
