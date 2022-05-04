#include <SFML/Network.hpp>
#include "queue.h"
#include "list.h"
#include"util.hpp"

class Accepter
{
private:
    queue<message>& m_queue;
    List<std::shared_ptr<sf::TcpSocket>>& m_socket;

public:
    Accepter(queue<message>& q, List<std::shared_ptr<sf::TcpSocket>>& s);
    void operator()();
};

