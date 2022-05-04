#pragma once
#include <vector>
#include "Bubble.h"
#include <SFML/Graphics.hpp>

class grid
{
public:
	int gridHeight;
	int gridWidth;
	int columns = 14;
	int rows = 12;
	int radius = 15;
	std::vector<std::vector<Bubble*>> g_tiles;
	bool BubblesInterest(int row, int column);
	void DeletedBubbles(int row, int column, sf::Color TargetColour);
	int destroyedBalls;
	int tileWidth;
	int tileHeight;
};


