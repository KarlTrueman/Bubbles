#include <SFML/Network.hpp>
#include "queue.hpp"
#include"util.hpp"

class receiver {
public:
    receiver(std::shared_ptr<sf::TcpSocket> s, Queue < message >& queue);
    void recv_loop();
private:
    std::shared_ptr<sf::TcpSocket> m_socket;
    Queue<message>& m_queue;
};