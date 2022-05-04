#include "grid.h"
#include "Grid.h"

bool grid::BubblesInterest(int row, int column)
{
	//Collision code to loop through which bubbles match and if they need deleting
	sf::Color GridColor = g_tiles[row][column]->getColour();

	if (row > 0 && (g_tiles[row - 1][column]->isActive()) && (g_tiles[row - 1][column]->getColour() == GridColor)
		|| (row < (rows + 4) - 1 && g_tiles[row + 1][column]->isActive() && g_tiles[row + 1][column]->getColour() == GridColor)
		|| (column > 0 && g_tiles[row][column - 1]->isActive() && g_tiles[row][column - 1]->getColour() == GridColor)
		|| (column < columns - 1 && g_tiles[row][column + 1]->isActive() && g_tiles[row][column + 1]->getColour() == GridColor)) {
		if (row % 2 != 0 && g_tiles[row + 1][column + 1]->isActive() && g_tiles[row - 1][column + 1]->getColour() == GridColor)
		{
			DeletedBubbles(row, column, GridColor);
		}
		else if (row % 2 == 0 && g_tiles[row + 1][column - 1]->isActive() && g_tiles[row - 1][column - 1]->getColour() == GridColor)
		{
			DeletedBubbles(row, column, GridColor);
		}
		else
		{
			DeletedBubbles(row, column, GridColor);
		}
		return true;
	}
	return false;
}

void grid::DeletedBubbles(int row, int column, sf::Color GridColor)
{
	if (row < 0) return;
	if (row >= 4 + rows) return;
	if (column < 0) return;
	if (column >= columns) return;
	if (!g_tiles[row][column]->isActive()) return;
	if (g_tiles[row][column]->getColour() != GridColor) return;
	// if function is still going after these if statements then current ball is part of the cluster

	g_tiles[row][column]->setActive(false);
	destroyedBalls++;
	DeletedBubbles(row, column + 1, GridColor);
	DeletedBubbles(row, column - 1, GridColor);
	DeletedBubbles(row + 1, column, GridColor);
	DeletedBubbles(row - 1, column, GridColor);
	if (row % 2 != 0)
	{
		DeletedBubbles(row - 1, column + 1, GridColor);
	}
	else
	{
		DeletedBubbles(row - 1, column - 1, GridColor);
	}
}