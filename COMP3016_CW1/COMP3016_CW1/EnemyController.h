#pragma once
#include <vector>
#include "Maze.h"
#include "Enemy.h"
#include "Spinner.h"

class EnemyController
{
public:
	EnemyController(SDL_Renderer* renderer, int level);
	~EnemyController();
	void UpdateEnemies(Maze* maze, SDL_Renderer* renderer);
	void LaserCheck(int x, int y, bool& shouldDestroy);
private:
	std::vector<Enemy*> enemies;
};