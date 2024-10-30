#pragma once
#include "Constants.h"
#include "SDL_mixer.h"
#include "Maze.h"
#include "Laser.h"
#include "Score.h"

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
	void RenderLasers(SDL_Renderer* renderer, Maze* maze, EnemyController* enemyController, Score* score);
	int getX() const { return x; }
	int getY() const { return y; }
	float getAngle() const { return angle; }
private:
	int x;
	int y;
	float angle;
	Laser* lasers[PLAYER_SHOTS];
	Mix_Chunk* laserSFX;
	int lastShotTime;
};

