#include "receiver.h"
#include "util.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <tuple>

int Client()
{
    std::shared_ptr<sf::TcpSocket> socket_ptr = std::make_shared<sf::TcpSocket>();
    // Sending a "register" message
    std::string userName;
    std::cout << "Please type in your user name: ";
    std::cin >> userName; // Not a getline
    // TODO: send the registration message consisting of the user name.
    // register:userName

    Queue<message> queue;
    Receiver myReceiver{socket_ptr, queue};
    // TODO: launch a receiver thread

    std::string s = "";
    std::getline(std::cin, s); // Flushing the last end of line
    while (true)
    {
        // 1 Input from the player
        s = "";
        std::getline(std::cin, s);
        std::cout << "Sending: \"" << s << "\"" << std::endl;
        std::stringstream ss;
        ss << "message:" << s;
    }
    return 0;
}
