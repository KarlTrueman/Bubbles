#pragma once
#include "Bubble.h"
#include "Grid.h"

class Player
{
public:
	grid gridOfBubbles;
	Bubble player;
	sf::RectangleShape playerCannon;

	int playerAngle;
	bool isCannonReady = true;
	int playerScore;
	int playerColour;

	sf::Vector2f originalPos;
	void setBubblePosition(int x, int y);
	void setVel(sf::Vector2f newVel);
	void SetScore(int add_Score);
	bool checkCollisions(float x1, float y1, float r1, float x2, float y2, float r2);
	void addToGrid(Bubble* otherBubble);
	void resetPlayerBall(sf::Color newColour, sf::Vector2f pos);
	bool cluster(int row, int column);
};
