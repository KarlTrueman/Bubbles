#include <SFML/Network.hpp>
#include "queue.h"
#include"util.hpp"

class receiver {
public:
    receiver(std::shared_ptr<sf::TcpSocket> s, queue < message >& queue);
    void recv_loop();
private:
    std::shared_ptr<sf::TcpSocket> m_socket;
    queue<message>& m_queue;
};