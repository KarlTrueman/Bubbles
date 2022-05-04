#include "bubble.h"

sf::Vector2f bubble::getPos()
{
	sf::Vector2f bubblePos = bubble.getPosition();
	sf::Vector2f addRadius(20, 20);
	bubblePos += addRadius;
	return bubblePos;
}

sf::Color bubble::getColour()
{
    return sf::Color();
}

bool bubble::isActive()
{
    return false;
}

void bubble::setBubblePos(sf::Vector2f pos)
{
}

void bubble::setBubbleColour(sf::Color fillColour)
{
}

void bubble::setActive(bool active)
{
}

void bubble::setBubbleOrigin(sf::Vector2f origin)
{
}

void bubble::setBubbleVel(sf::Vector2f newVel)
{
}

void bubble::setBubbleRadius(int radius)
{
}

void bubble::move()
{
}
