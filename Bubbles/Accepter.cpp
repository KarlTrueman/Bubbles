#include "accepter.h"
#include "receiver.h"
#include "util.hpp"
#include <iostream>
#include <sstream>
#include <thread>

Accepter::Accepter(Queue<message>& q, List<std::shared_ptr<sf::TcpSocket>>& s) :
    m_queue(q),
    socket_(s)
{}

void Accepter::operator()()
{
    int player = 1;
    unsigned int seed = time(NULL);
    sf::TcpListener listener;
    if (listener.listen(55002) != sf::Socket::Done)
    {
        std::cerr << "Error on port:\n";
        return;
    }
    std::cout << "Bound to port\n";

    while (1)
    {
        std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
        //Accepting a connection on socket
        if (listener.accept(*socket) != sf::Socket::Done)
        {
            std::cerr << "cant accept connection\n";
            return;
        }
        socket_.push(socket);
        std::stringstream ss;
        ss << "Accepted a connection from: "
            << socket->getRemoteAddress()
            << ":"
            << socket->getRemotePort()
            << std::endl;
        std::cout << ss.str();
        std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>(socket, m_queue);

        sf::Packet SeedPacket;
        SeedPacket << player << seed;
        sf::Packet seedSend = SeedPacket;
        seedSend << player << seed;
        sf::Socket::Status statusSeed = socket->send(seedSend);
        if (statusSeed != sf::Socket::Done)
        {

        }
        player++;


        std::thread(&Receiver::recv_loop, receiver).detach();
    }
}
