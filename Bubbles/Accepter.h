#include <SFML/Network.hpp>
#include "queue.hpp"
#include "list.h"
#include"util.hpp"

class Accepter
{
private:
    Queue<message>& m_queue;
    List<std::shared_ptr<sf::TcpSocket>>& m_socket;

public:
    Accepter(Queue<message>& q, List<std::shared_ptr<sf::TcpSocket>>& s);
    void operator()();
};

