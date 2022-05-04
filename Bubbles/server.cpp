#include "server.h"
#include "accepter.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "queue.hpp"
#include "list.h"
#include "receiver.h"
#include "util.hpp"
#include "UDPreceiver.h"

void server::ServerCreation()
{
    Queue<message> queue;
    List<std::shared_ptr<sf::TcpSocket>> sockets;
    sf::UdpSocket Usocket;
    unsigned int local_port = 55000;
    if (Usocket.bind(local_port) != sf::Socket::Done)
    {
        std::cerr << "Failed to bind to port";
        exit;
    }

    std::thread(Accepter(queue, sockets)).detach();
    std::shared_ptr<UDPreceiver> reciever = std::make_shared<UDPreceiver>(Usocket);
    std::thread(&UDPreceiver::receive, reciever).detach();
    sf::IpAddress recipient;
    unsigned short remote_port;

    while (1)
    {
        auto s = queue.pop();
        sf::Packet packet1 = std::get<1>(s);
        sf::TcpSocket* otherPacket = std::get<0>(s);
        //std::cout << "main read: \"" << s.angle << "\"\n";
        auto send = [&packet1, &otherPacket](std::shared_ptr<sf::TcpSocket> socket)
        {
            sf::TcpSocket* current = socket.get();
            short c = current->getLocalPort();
            sf::TcpSocket* other = socket.get();
            short os = other->getLocalPort();
            sf::Socket::Status status;
            if (current != otherPacket)
            {
                status = socket->send(packet1);
                if (status != sf::Socket::Done)
                {
                    std::cerr << "Error sending packet\n";
                }
            }
            else
            {
                return;
            }
        };
        sockets.for_each(send);
    }
}
