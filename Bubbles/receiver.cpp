#include "receiver.h"
#include "util.hpp"
#include <chrono>
#include <cstring>
#include <iostream>
#include <iostream>
#include <sstream>
#include <thread>
#include <tuple>

receiver::receiver(std::shared_ptr<sf::TcpSocket> s, Queue<message> &q) :
    m_socket(s),
    m_queue(q)
{
}

void receiver::recv_loop()
{
    sf::Packet buffer;
    size_t remote_port;
    size_t p;
    while (1)
    {
        // TODO receive a message here
        if (m_socket->receive(buffer) != sf::Socket::Done)
        {
            std::cout << "Error receiving message\n";
            return;
        }
        sf::TcpSocket* t = m_socket.get();
        m_queue.push(std::make_pair(m_socket.get(), buffer));
    }
}