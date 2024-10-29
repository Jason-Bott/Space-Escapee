#pragma once
#include "Constants.h"
#include "Maze.h"

class EnemyController;

class Laser
{
public:
	Laser(int x, int y, float angle) : x(x), y(y), angle(angle) {};
	void Move(Maze* maze, bool& shouldDestroy);
	void CheckForEnemies(EnemyController* enemyController, bool& shouldDestroy);
	void CheckForPlayer(int playerX, int playerY, bool& shouldDestroy);
	int getX() const { return x; }
	int getY() const { return y; }
	float getAngle() const { return angle; }
private:
	int x;
	int y;
	float angle;
};