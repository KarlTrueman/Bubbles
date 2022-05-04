#include "server.h"
#include "receiver.h"
#include "Accepter.h"
#include "util.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <tuple>
#include"UDPReceiver.h"
#include "queue.hpp"
#include "list.h"
#define BUFF_SIZE 1024

void server::Server()
{
    Queue<message> queue;
    List<std::shared_ptr<sf::TcpSocket>> sockets;
    sf::UdpSocket socket;
    unsigned int local_port = PORT;
    // TODO: we need to bind our socket to a port
    if (socket.bind(local_port) != sf::Socket::Done)
    {
        std::cout << "Error binding to port: " << local_port << "\n";
		exit(0);
    }
    else
    {
        std::cout << "Server bound to port: " << local_port << "\n";
    }
    // TODO: we need to start a receiver thread.
    std::thread(Accepter(queue, sockets)).detach();
    std::shared_ptr<UDPreceiver> receiver = std::make_shared<UDPreceiver>(socket);
    std::thread(&UDPreceiver::recv, receiver).detach();
    sf::IpAddress recipient;
    unsigned short remote_port;

    sf::Packet seed;
    bool IsGameRunning = true;

	while (IsGameRunning)
	{


		auto p = queue.pop();
		sf::Packet packet = std::get<1>(p);
		sf::TcpSocket* otherSocket = std::get<0>(p);
		auto sendToOne = [&packet, &otherSocket](std::shared_ptr<sf::TcpSocket> socket) {
			// unsigned short sent;
			// Make sure we sent to the OTHER clients, no to the original sender
			sf::TcpSocket* currentSocket = socket.get();
			short cs = currentSocket->getLocalPort();
			short os = otherSocket->getLocalPort();
			sf::Socket::Status status;
			if (currentSocket != otherSocket)
			{
				status = socket->send(packet);
				if (status != sf::Socket::Done)
				{
					/* code */
				}
			}
			else
			{
				return;
			}

		};
		sockets.for_each(sendToOne);

	}
}
