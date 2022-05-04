#pragma once

#include "queue.hpp"
#include "list.h"
#include <SFML/Network.hpp>
#include "util.hpp"

class Accepter {
private:
    Queue<message>& m_queue;
    List<std::shared_ptr<sf::TcpSocket>>& socket_;

public:
    Accepter(Queue<message>& q, List<std::shared_ptr<sf::TcpSocket>>& s);
    void operator()();
};