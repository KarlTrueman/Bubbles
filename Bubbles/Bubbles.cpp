#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <SFML/Network.hpp>
#include "queue.hpp"
#include "receiver.h"
#include "server.h"
#include <thread>
#include <windows.h>


#define BUBBLE_SIZE 20
#define CANNON_H  60
#define CANNON_W  20
#define MAX_ANGLE 80
#define MIN_ANGLE 280
#define M_PI      3.141692654
#define VELOCITY  7
#define WINDOW_H  600
#define WINDOW_W  1200
#define BUFF_SIZE 1024

class move_msg
{
public:
    sf::Uint32 id;
    int ballcolour;
    float posX;
    float posY;
    float velocityX;
    float velocityY;
    int score;
    int cannon_angle;
    bool isCannonReady;
};

int main(int argc, const char* argv[])
{
    srand(time(NULL));

    //Setting up the queue, recipient and server
    Queue<message> queue;
    sf::IpAddress recipient = sf::IpAddress::Broadcast;
    server serv;

    //Broadcast message
    std::string msg = "msg";
    sf::Packet packet1;
    packet1 << msg;
    sf::UdpSocket testingServer;
    unsigned short remote_port = 55001;
    sf::Socket::Status status = testingServer.send(msg.c_str(), msg.length(), recipient, 55000);
    if (status != sf::Socket::Done)
    {
        std::cout << "Problem Sending Broadcast\n";
        return 1;
    }
    else
    {
        std::cout << "Broadcasting\n";
    }

    char data[BUFF_SIZE];
    std::size_t received;
    std::memset(data, 0, BUFF_SIZE);

    //Unblock the UDP socket so that it will let in messages and create a server if no messages are recieved
    testingServer.setBlocking(false);
    Sleep(1500);
    if (testingServer.receive(data, BUFF_SIZE, received, recipient, remote_port) != sf::Socket::Done)
    {
        std::cout << "Setting Up Server Now\n";
        std::thread(&server::Server, &serv).detach();
        Sleep(1500);
        if (testingServer.send(packet1, sf::IpAddress::Broadcast, 55000) != sf::Socket::Done)
        {
            std::cout << "Problem Sending Brodcast\n";
            return 1;
        }
        Sleep(1500);
        if (testingServer.receive(data, BUFF_SIZE, received, recipient, remote_port) != sf::Socket::Done)
        {
            std::cout << "Failed to connect to self\n";
        }
        else
        {
            std::cout << "Connected to self\n";
        }
    }
    else
    {
        std::cout << "Connected to other server\n" << std::endl;
    }
    testingServer.setBlocking(true);

    std::shared_ptr<sf::TcpSocket> tcp = std::make_shared<sf::TcpSocket>();
    //Spawn server if cannot find another server
    if (tcp->connect(sf::IpAddress::getLocalAddress(), 55002) != sf::Socket::Done)
    {
        std::cout << "Unable to Connect to Server\n";
        return 1;
    }
    std::cout << "Connected to the Server\n";

    sf::Packet introP;
    //status = tcp->receive(introP);
    if (tcp->receive(introP) != sf::Socket::Done)
    {
        std::cout << "Error receiving seed\n";
        return 0;
    }
    std::cout << "Seed Recieved\n";

    int player_number = 0;
    unsigned int setUp = 0;
    introP >> player_number >> setUp;
    std::cout << "Game setup: " << setUp << " Player Number: " << player_number << std::endl;
    srand(setUp);
    std::shared_ptr<receiver> myReceiver = std::make_shared<receiver>(tcp, queue);
    std::thread(&receiver::recv_loop, myReceiver).detach();



    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Bubble");
    window.setFramerateLimit(60);

    int cooldown1 = 20;
    int cooldown2 = 20;


    const sf::Color colours[5] = {
        sf::Color::Red,
        sf::Color(127, 192, 127),
        sf::Color::Blue,
        sf::Color(192, 192, 127),
        sf::Color(127, 192, 192),
    };

    std::vector<sf::CircleShape> bubbles;
    for (size_t i = 1; i < 11; i++) {
        for (size_t j = 0; j < (WINDOW_W / 2) / 40 - (i % 2); j++) {
            sf::CircleShape bubble(BUBBLE_SIZE);
            bubble.setPosition(sf::Vector2f(BUBBLE_SIZE * 2 * j + (i % 2) * BUBBLE_SIZE, i * 33));
            int points = rand() % 5;
            bubble.setFillColor(colours[points]);
            bubbles.push_back(bubble);
        }
    }

    std::vector<sf::CircleShape> bubbles2;
    for (size_t i = 1; i < 11; i++) {
        for (size_t j = 0; j < (WINDOW_W / 2) / 40 - (i % 2); j++) {
            sf::CircleShape bubble(BUBBLE_SIZE);
            bubble.setPosition(sf::Vector2f((BUBBLE_SIZE * 2 * j + (i % 2) * BUBBLE_SIZE) + WINDOW_W/2, i * 33));
            int points = rand() % 5;
            bubble.setFillColor(colours[points]);
            bubbles2.push_back(bubble);
        }
    }

    std::vector<sf::CircleShape> bubblesOI;

    sf::RectangleShape cannon1(sf::Vector2f(CANNON_W, CANNON_H));
    cannon1.setOrigin(CANNON_W / 2, CANNON_H);
    sf::Vector2f p1_pos(WINDOW_W / 4, (WINDOW_H));
    cannon1.setOrigin(CANNON_W / 2, CANNON_H);
    cannon1.setPosition(p1_pos);
    float angle1{ 0 };
    bool isCannon1Ready{ true };

    sf::RectangleShape cannon2(sf::Vector2f(CANNON_W, CANNON_H));
    cannon2.setOrigin(CANNON_W / 2, CANNON_H);
    sf::Vector2f p2_pos(3 * WINDOW_W / 4, (WINDOW_H));
    cannon2.setPosition(p2_pos);
    float angle2 = 0;
    bool isCannon2Ready{ true };

    sf::RectangleShape wall(sf::Vector2f(1, WINDOW_H));
    wall.setPosition(WINDOW_W / 2, 0);

    sf::CircleShape ball1(BUBBLE_SIZE);
    ball1.setOrigin(BUBBLE_SIZE, BUBBLE_SIZE);
    ball1.setPosition(p1_pos);
    ball1.setFillColor(colours[rand() % 5]);
    float dx1{ 0 };
    float dy1{ 0 };

    sf::CircleShape ball2(BUBBLE_SIZE);
    ball2.setOrigin(BUBBLE_SIZE, BUBBLE_SIZE);
    ball2.setPosition(p2_pos);
    ball2.setFillColor(colours[rand() % 5]);
    float dx2{ 0 };
    float dy2{ 0 };

    sf::Font font;
    if (!font.loadFromFile("PressStart2P.ttf"))
    {
        return 1;
    }
    sf::Text score("0 0", font);
    score.setCharacterSize(30);
    score.setPosition(WINDOW_W / 2 - 44, 10);
    int score1 = 0;
    int score2 = 0;

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }

        angle1 = cannon1.getRotation();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (angle1 > MIN_ANGLE + 1 || angle1 < MAX_ANGLE + 1))
            cannon1.rotate(-1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (angle1 > MIN_ANGLE - 1 || angle1 < MAX_ANGLE - 1))
            cannon1.rotate(1);
        angle2 = cannon2.getRotation();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (angle2 > MIN_ANGLE + 1 || angle2 < MAX_ANGLE + 1))
            cannon2.rotate(-1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (angle2 > MIN_ANGLE - 1 || angle2 < MAX_ANGLE - 1))
            cannon2.rotate(1);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isCannon1Ready)
        {
            angle1 = cannon1.getRotation();
            dx1 = -cos((angle1 + 90) * M_PI / 180) * VELOCITY;
            dy1 = -sin((angle1 + 90) * M_PI / 180) * VELOCITY;
            isCannon1Ready = false;
        }

        if (isCannon1Ready == false)
        {
            cooldown1--;
        }

        if (cooldown1 == 0)
        {
            isCannon1Ready = true;
            cooldown1 = 100;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isCannon2Ready)
        {
            angle2 = cannon2.getRotation();
            dx2 = -cos((angle2 + 90) * M_PI / 180) * VELOCITY;
            dy2 = -sin((angle2 + 90) * M_PI / 180) * VELOCITY;
            isCannon2Ready = false;
        }

        if (dx1 != 0 && dy1 != 0)
        {
            ball1.move(dx1, dy1);
            sf::Vector2f pos = ball1.getPosition();
            if (pos.x < BUBBLE_SIZE || pos.x > WINDOW_W / 2 - BUBBLE_SIZE) {
                dx1 = -dx1;
            }

            bool collided1 = false;
            for (int i = 0; i < bubbles.size(); i++)
            {
                float x = bubbles[i].getPosition().x + BUBBLE_SIZE - pos.x;
                float y = bubbles[i].getPosition().y + BUBBLE_SIZE - pos.y;

                if (size_t(x * x) + y * y <= size_t(BUBBLE_SIZE) * BUBBLE_SIZE * 4)
                {
                    //std::cout << "Collided\n";

                    collided1 = true;

                    if (bubbles[i].getFillColor().toInteger() == ball1.getFillColor().toInteger())
                    {
                        //std::cout << "SameColour\n";
                    }
                }
            }

            if (collided1)
            {
                dx1 = 0;
                dy1 = 0;

                sf::CircleShape bubble(BUBBLE_SIZE);
                bubble.setPosition(ball1.getPosition().x - BUBBLE_SIZE, ball1.getPosition().y - BUBBLE_SIZE);
                bubble.setFillColor(ball1.getFillColor());
                bubbles.push_back(bubble);

                ball1.setFillColor(colours[rand() % 5]);
                ball1.setPosition(p1_pos);
                isCannon1Ready = true;

                for (int i = 0; i < bubbles.size(); i++)
                {
                    if (!bubbles[i].BubbleChecked)
                    {
                        for (int j = 0; j < bubbles.size(); j++)
                        {
                            if (!bubbles[j].BubbleChecked)
                            {
                                float x = bubbles[i].getPosition().x + BUBBLE_SIZE - bubbles[j].getPosition().x + BUBBLE_SIZE;
                                float y = bubbles[i].getPosition().y + BUBBLE_SIZE - bubbles[j].getPosition().y + BUBBLE_SIZE;
                                if (size_t(x * x) + y * y <= size_t(BUBBLE_SIZE) * BUBBLE_SIZE * 4 && bubbles[i].getFillColor() == bubbles[j].getFillColor())
                                {
                                    bubblesOI.push_back(bubbles[i]);
                                    bubblesOI.push_back(bubbles[j]);
                                    bubbles[j].BubbleChecked = true;
                                }
                            }
                        }
                    }
                    bubbles[i].BubbleChecked = true;
                }

                //ting
            }

        }

        if (dx2 != 0 && dy2 != 0)
        {
            ball2.move(dx2, dy2);
            sf::Vector2f pos = ball2.getPosition();
            if (pos.x < WINDOW_W / 2 + BUBBLE_SIZE || pos.x > WINDOW_W - BUBBLE_SIZE) 
            {
                dx2 = -dx2;
            }
            bool collided2 = false;
            for (int i = 0; i < bubbles2.size(); i++)
            {
                float x = bubbles2[i].getPosition().x + BUBBLE_SIZE - pos.x;
                float y = bubbles2[i].getPosition().y + BUBBLE_SIZE - pos.y;

                if (size_t(x * x) + y * y <= size_t(BUBBLE_SIZE) * BUBBLE_SIZE * 4)
                {
                    //std::cout << "Collided\n";

                    collided2 = true;

                    if (bubbles2[i].getFillColor().toInteger() == ball2.getFillColor().toInteger())
                    {
                        //std::cout << "SameColour\n";
                    }
                }
            }

            if (collided2)
            {
                dx2 = 0;
                dy2 = 0;

                sf::CircleShape bubble(BUBBLE_SIZE);
                bubble.setPosition(ball2.getPosition().x - BUBBLE_SIZE, ball2.getPosition().y - BUBBLE_SIZE);
                bubble.setFillColor(ball2.getFillColor());
                bubbles2.push_back(bubble);

                ball2.setFillColor(colours[rand() % 5]);
                ball2.setPosition(p2_pos);
                isCannon2Ready = true;
            }
        }

        window.clear();
        window.draw(cannon1);
        window.draw(cannon2);
        window.draw(wall);
        window.draw(score);
        window.draw(ball1);
        window.draw(ball2);
        for (auto& b : bubbles) 
        {
            window.draw(b);
        }

        for (auto& b : bubbles2)
        {
            window.draw(b);
        }
    window.display();
    }
    return 0;
}
