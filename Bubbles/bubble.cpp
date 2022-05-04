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
	return bubble.getFillColor();
}

bool bubble::isActive()
{
    return active;
}

void bubble::setBubblePos(sf::Vector2f pos)
{
	bubble.setPosition(pos);
}

void bubble::setBubbleColour(sf::Color fillColour)
{
	bubble.setFillColor(fillColour);
}

void bubble::setActive(bool isActive)
{
	active = isActive;
}

void bubble::setBubbleOrigin(sf::Vector2f origin)
{
	bubble.setOrigin(origin);
}

void bubble::setBubbleVel(sf::Vector2f newVel)
{
	vel = newVel;
}

void bubble::setBubbleRadius(int radius)
{
	bubble.setRadius(radius);
}

void bubble::move()
{
	bubble.move(vel);
}
