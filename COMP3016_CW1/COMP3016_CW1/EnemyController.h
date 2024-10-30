#pragma once
#include <vector>
#include "Maze.h"
#include "Enemy.h"
#include "Spinner.h"
#include "Roamer.h"
#include "Patroller.h"

class EnemyController
{
public:
	EnemyController(SDL_Renderer* renderer, int level);
	~EnemyController();
	void UpdateEnemies(Maze* maze, SDL_Renderer* renderer, EnemyController* enemyController, Score* score, int playerX, int playerY, bool& isRunning);
	void LaserCheck(int x, int y, bool& shouldDestroy);
private:
	std::vector<Enemy*> enemies;
};