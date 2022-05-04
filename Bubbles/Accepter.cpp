#include "accepter.h"
#include "receiver.h"
#include <iostream>
#include <sstream>
#include <thread>

Accepter::Accepter(Queue<message>& q, List<std::shared_ptr<sf::TcpSocket>>& s) :
    m_queue(q),
    m_socket(s)
{}

void Accepter::operator()()
{
    int player = 1;
    unsigned int seed = time(NULL);
    sf::TcpListener listener;
    // TODO the listener has to listen.
    if (listener.listen(4304) != sf::Socket::Done)
    {
        std::cerr << "Error listening to port \n";
        return;
    }
    std::cout << "Bound to port\n";
    while (true)
    {
        std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
        // TODO accept a connection on socket
        if (listener.accept(*socket) != sf::Socket::Done)
        {
            std::cout << "Connection failed\n";
            return;
        }
        m_socket.push(socket);
        std::stringstream ss;
        ss << "Accepted connection: "
            << socket->getRemoteAddress()
            << ":"
            << socket->getRemotePort()
            << std::endl;
        std::cout << ss.str();
        std::shared_ptr<receiver> receiver = std::make_shared<receiver>(socket, m_queue);
        sf::Packet seedName;
        seedName << player << seed;
        sf::Packet seedSend = seedName;

        seedSend << player << seed;
        sf::Socket::Status statusSeed = socket->send(seedSend);
        if (statusSeed != sf::Socket::Done)
        {

        }
        player++;
        // TODO launch a thread to receive with the receiver
        std::thread(&receiver::recv_loop, receiver).detach();
    }
}
