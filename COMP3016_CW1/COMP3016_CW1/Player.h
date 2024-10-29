#pragma once
#include "Constants.h"
#include "Maze.h"
#include "Laser.h"

class Player
{
public:
	Player(int x, int y);
	~Player();
	void MoveUp(Maze* maze);
	void MoveLeft(Maze* maze);
	void MoveDown(Maze* maze);
	void MoveRight(Maze* maze);
	void Shoot();
	void RenderLasers(SDL_Renderer* renderer, Maze* maze, EnemyController* enemyController);
	int getX() const { return x; }
	int getY() const { return y; }
	float getAngle() const { return angle; }
private:
	int x;
	int y;
	float angle;
	Laser* lasers[PLAYER_SHOTS];
	int lastShotTime;
};

