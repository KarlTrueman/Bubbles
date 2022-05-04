#include "Grid.h"

bool grid::GroupOI(int row, int column)
{
	sf::Color targetColour = g_tiles[row][column]->getColour();

	if (row > 0 && (g_tiles[row - 1][column]->isActive()) && (g_tiles[row - 1][column]->getColour() == targetColour)
		|| (row < (rows + 4) - 1 && g_tiles[row + 1][column]->isActive() && g_tiles[row + 1][column]->getColour() == targetColour)
		|| (column > 0 && g_tiles[row][column - 1]->isActive() && g_tiles[row][column - 1]->getColour() == targetColour)
		|| (column < columns - 1 && g_tiles[row][column + 1]->isActive() && g_tiles[row][column + 1]->getColour() == targetColour)) {
		if (row % 2 != 0 && g_tiles[row + 1][column + 1]->isActive() && g_tiles[row - 1][column + 1]->getColour() == targetColour)
		{
			deleteGroupOI(row, column, targetColour);
		}
		else if (row % 2 == 0 && g_tiles[row + 1][column - 1]->isActive() && g_tiles[row - 1][column - 1]->getColour() == targetColour)
		{
			deleteGroupOI(row, column, targetColour);
		}
		else
		{
			deleteGroupOI(row, column, targetColour);
		}
		return true;
	}
	return false;
}

void grid::deleteGroupOI(int row, int column, sf::Color TargetColour)
{
	if (row < 0) return;
	if (row >= 4 + rows) return;
	if (column < 0) return;
	if (column >= columns) return;
	if (!g_tiles[row][column]->isActive()) return;
	if (g_tiles[row][column]->getColour() != TargetColour) return;
	// if function is still going after these if statements then current ball is part of the cluster

	g_tiles[row][column]->setActive(false);
	destroyedBalls++;
	deleteGroupOI(row, column + 1, TargetColour);
	deleteGroupOI(row, column - 1, TargetColour);
	deleteGroupOI(row + 1, column, TargetColour);
	deleteGroupOI(row - 1, column, TargetColour);
	if (row % 2 != 0)
	{
		deleteGroupOI(row - 1, column + 1, TargetColour);
	}
	else
	{
		deleteGroupOI(row - 1, column - 1, TargetColour);
	}
}
