#include "receiver.h"
#include "util.hpp"
#include <chrono>
#include <cstring>
#include <iostream>
#include <iostream>
#include <sstream>
#include <thread>


Receiver::Receiver(std::shared_ptr<sf::TcpSocket> s, Queue<message>& q) :
    socket_(s),
    m_queue(q)
{
}

void Receiver::recv_loop()
{
    char buffer[256];
    {
        std::stringstream ss;
        ss << socket_->getRemoteAddress() << ":" << socket_->getRemotePort() << std::endl;
        std::cout << ss.str();
    }
    std::size_t received;
    sf::Packet packet;
    while (1)
    {

        if (socket_->receive(packet) != sf::Socket::Done)
        {
            std::cout << "Cannont receive packet from client\n";
            return;
        }
        sf::TcpSocket* tcp = socket_.get();
        m_queue.push(std::make_pair(socket_.get(), packet));
    }
}