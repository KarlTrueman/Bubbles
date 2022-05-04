#include "Bubble.h"

void Bubble::setBubblePosition(sf::Vector2f pos)
{
	bubble.setPosition(pos);
}

void Bubble::setBubbleColour(sf::Color fillColour)
{
	bubble.setFillColor(fillColour);
}

void Bubble::setActive(bool isActive)
{
	active = isActive;
}

void Bubble::setVel(sf::Vector2f newVel)
{
	vel = newVel;
}

void Bubble::setRadius(int radius)
{
	bubble.setRadius(radius);
}

void Bubble::setBubbleOrigin(sf::Vector2f origin)
{
	bubble.setOrigin(origin);
}

void Bubble::move()
{
	bubble.move(vel);
}

sf::Vector2f Bubble::getPos()
{
	sf::Vector2f bubblePos = bubble.getPosition();
	sf::Vector2f addRadius(20, 20);
	bubblePos += addRadius;
	return bubblePos;
}

bool Bubble::isActive()
{
	return active;
}

sf::Color Bubble::getColour()
{
	return bubble.getFillColor();
}