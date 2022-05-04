#include "Player.h"

void Player::SetScore(int add_score)
{
	playerScore += add_score;
}

void Player::setBubblePosition(int x, int y)
{
	player.pos.x = x;
	player.pos.y = y;
}

void Player::setVel(sf::Vector2f newVel)
{
	player.setVel(newVel);
}



bool Player::checkCollisions(float x1, float y1, float r1, float x2, float y2, float r2)
{

	if (((y1 - (20 + y2)) * (y1 - (20 + y2))) + ((x1 - (20 + x2)) * (x1 - (20 + x2))) <= 20 * 4 * 20)
	{
		return true;

	}

	return false;
}

void Player::addToGrid(Bubble* other)
{
	int centerX = player.bubble.getPosition().x + gridOfBubbles.radius;
	int centerY = player.bubble.getPosition().y + gridOfBubbles.radius;
	int centerX2 = other->bubble.getPosition().x + gridOfBubbles.radius;
	int centerY2 = other->bubble.getPosition().y + gridOfBubbles.radius;
	sf::Vector2f gridPos = sf::Vector2f(other->gridPos.x, other->gridPos.y);
	int gridPositionX = gridPos.x;
	float distance = sqrtf(powf(player.getPos().x - other->getPos().x, 2) +
		powf(player.getPos().y - other->getPos().y, 2));
	player.bubble.getRadius();
	float closest = 1000;
	float next;
	int closestRow = gridPos.x, closestColumn = gridPos.y;
	if (gridPos.x < (gridOfBubbles.rows + 4) - 1 && !gridOfBubbles.g_tiles[gridPos.x + 1][gridPos.y]->active)
	{
		next = sqrtf(powf((player.getPos().x - gridOfBubbles.g_tiles[gridPos.x + 1][gridPos.y]->getPos().x), 2) + powf((player.bubble.getPosition().y - gridOfBubbles.g_tiles[gridPos.x + 1][gridPos.y]->bubble.getPosition().y), 2));
		if (closest > next)
		{
			closest = next;
			closestRow = gridPos.x + 1;
			closestColumn = gridPos.y;
		}
	}
	if (gridPos.y > 0 && !gridOfBubbles.g_tiles[gridPos.x][gridPos.y - 1]->active)
	{
		next = sqrtf(powf((player.bubble.getPosition().x - gridOfBubbles.g_tiles[gridPos.x][gridPos.y - 1]->bubble.getPosition().x), 2) + powf((player.bubble.getPosition().y - gridOfBubbles.g_tiles[gridPos.x][gridPos.y - 1]->bubble.getPosition().y), 2));
		if (closest > next)
		{
			closest = next;
			closestRow = gridPos.x;
			closestColumn = gridPos.y - 1;
		}
	}
	if (gridPos.y < gridOfBubbles.columns - 1 && !gridOfBubbles.g_tiles[gridPos.x][gridPos.y + 1]->active)
	{
		next = sqrtf(powf((player.bubble.getPosition().x - gridOfBubbles.g_tiles[gridPos.x][gridPos.y + 1]->getPos().x), 2) + powf((player.bubble.getPosition().y - gridOfBubbles.g_tiles[gridPos.x][gridPos.y + 1]->bubble.getPosition().y), 2));
		if (closest > next)
		{
			closest = next;
			closestRow = gridPos.x;
			closestColumn = gridPos.y + 1;
		}
	}
	player.setBubblePosition(gridOfBubbles.g_tiles[closestRow][closestColumn]->bubble.getPosition());
	gridOfBubbles.g_tiles[closestRow][closestColumn]->setBubbleColour(player.bubble.getFillColor());
	gridOfBubbles.g_tiles[closestRow][closestColumn]->setActive(true);

	if (gridOfBubbles.BubblesInterest(closestRow, closestColumn))
	{
		gridOfBubbles.DeletedBubbles(closestRow, closestColumn, player.getColour());
		isCannonReady = true;
	}

	isCannonReady = true;
}

void Player::resetPlayerBall(sf::Color newColour, sf::Vector2f position)
{
	player.setBubbleColour(newColour);
	player.setBubblePosition(position);
	player.setVel(sf::Vector2f(0, 0));
}

bool Player::cluster(int row, int column)
{
	sf::Color targetColor = gridOfBubbles.g_tiles[row][column]->getColour();
	if ((row > 0 && gridOfBubbles.g_tiles[row - 1][column]->isActive()) && (gridOfBubbles.g_tiles[row - 1][column]->getColour() == targetColor)
		|| (row < (gridOfBubbles.rows + 4) - 1 && gridOfBubbles.g_tiles[row + 1][column]->isActive() && gridOfBubbles.g_tiles[row + 1][column]->getColour() == targetColor)
		|| (column > 0 && gridOfBubbles.g_tiles[row][column - 1]->isActive() && gridOfBubbles.g_tiles[row][column - 1]->getColour() == targetColor)
		|| (column < gridOfBubbles.columns - 1 && gridOfBubbles.g_tiles[row][column + 1]->isActive() && gridOfBubbles.g_tiles[row][column + 1]->getColour() == targetColor)) {

		return true;
	}
	return false;
}
