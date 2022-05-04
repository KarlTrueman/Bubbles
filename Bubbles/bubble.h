#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>
class bubble
{
public:
	sf::Vector2f vel;
	sf::Vector2f pos;
	bool active = true;
	sf::CircleShape bubble;
	sf::Vector2f gridPos;
	sf::Vector2f getPos();

	sf::Color getColour();
	bool isActive();
	void setBubblePos(sf::Vector2f pos);
	void setBubbleColour(sf::Color fillColour);
	void setActive(bool isActive);
	void setBubbleOrigin(sf::Vector2f origin);
	void setBubbleVel(sf::Vector2f newVel);
	void setBubbleRadius(int radius);
	void move();

};

