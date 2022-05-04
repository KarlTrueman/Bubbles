#pragma once
#include <vector>
#include "Bubble.h"
#include <SFML/Graphics.hpp>

class grid
{
public:
	int gridHeight = 0;
	int gridWidth = 0;
	int columns = 14;
	int rows = 12;
	int radius = 15;
	std::vector<std::vector<Bubble*>> g_tiles;
	bool BubblesInterest(int row, int column);
	void DeletedBubbles(int row, int column, sf::Color TargetColour);
	int destroyedBalls = 0;
	int tileWidth = 0;
	int tileHeight = 0;
};


