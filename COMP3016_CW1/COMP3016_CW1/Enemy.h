#pragma once
#include "SDL.h"
#include "Constants.h"
#include "Maze.h"
#include "Laser.h"
#include "Score.h"

class Enemy
{
public:
	Enemy(int x, int y, int fireRate, const char* spriteFile, SDL_Renderer* renderer);
	~Enemy();
	virtual void Move(Maze* maze) = 0;
	virtual void Shoot();
	virtual void Render(SDL_Renderer* renderer);
	virtual void RenderLasers(SDL_Renderer* renderer, Maze* maze, EnemyController* enemyController, Score* score, int playerX, int playerY, bool& isRunning);
	int getX() const { return x; }
	int getY() const { return y; }
	float getAngle() const { return angle; }
protected:
	int x;
	int y;
	float angle;
	int fireRate;
	int lastShotTime;
	Laser* lasers[ENEMY_SHOTS];
	SDL_Texture* enemyTexture;
};