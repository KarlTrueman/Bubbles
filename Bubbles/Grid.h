#pragma once
#include <vector>
#include "bubble.h"
#include <SFML/Graphics.hpp>

class grid
{
public:
	int gridHeight;
	int gridWidth;
	int columns = 14;
	int rows = 12;
	int tileWidth;
	int tileHeight;
	int radius = 20;
	std::vector<std::vector<bubble*>> g_tiles;
	bool GroupOI(int row, int column);
	void deleteGroupOI(int row, int column, sf::Color TargetColour);
	int destroyedBalls;
};
