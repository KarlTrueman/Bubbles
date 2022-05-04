
#include "util.hpp"
#include <iostream>
#define PORT 4300

// Ignore this if you use your own send/receive/bind calls.

void net_run(std::function<sf::Socket::Status(void)> f, std::string error_message)
{
    sf::Socket::Status status = f();
    if (status != sf::Socket::Done)
    {
        std::cerr << "Failed to " << error_message << ": " << status << std::endl;
        perror(error_message.c_str());
        exit(0);
    }
}
