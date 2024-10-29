#include "EnemyController.h"
#include <cstdlib>
#include <ctime>

EnemyController::EnemyController(SDL_Renderer* renderer, int level) {
	srand(static_cast<unsigned>(time(0) * 2));
	int randomX = 0;
	int randomY = 0;

	for (int i = 0; i < level; i++) {
		randomX = MAZE_OFFSET + ((rand() % MAZE_WIDTH) * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		randomY = MAZE_OFFSET + ((rand() % MAZE_HEIGHT) * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		enemies.push_back(new Spinner(randomX, randomY, renderer));
	}
}

EnemyController::~EnemyController() {
	for (auto enemy : enemies) {
		delete enemy;
	}
}

void EnemyController::UpdateEnemies(Maze* maze, SDL_Renderer* renderer) {
	for (auto enemy : enemies) {
		enemy->Move(maze);
		enemy->Shoot();
		enemy->Render(renderer);
		enemy->RenderLasers(renderer, maze);
	}
}

void EnemyController::LaserCheck(int x, int y, bool& shouldDestroy) {
	for (auto enemy : enemies) {
		int enemyX = enemy->getX();
		int enemyY = enemy->getY();

		if (x > enemyX && x < enemyX + ENEMY_SIZE && y > enemyY && y < enemyY + ENEMY_SIZE) {
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
			shouldDestroy = true;
			return;
		}
	}
}