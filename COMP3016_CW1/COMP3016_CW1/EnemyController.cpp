#include "EnemyController.h"
#include <cstdlib>
#include <ctime>

EnemyController::EnemyController(SDL_Renderer* renderer, int level, int playerX, int playerY) {
	srand(static_cast<unsigned>(time(0) * 2));
	int randomX = 0;
	int randomY = 0;

	int spinners = (level / 5) + 2;
	if (level == 1) {
		spinners = 1;
	}

	for (int i = 0; i < spinners; i++) {
		int randomX = rand() % MAZE_WIDTH;
		while (randomX == playerX) {
			randomX = rand() % MAZE_WIDTH;
		}

		int randomY = rand() % MAZE_HEIGHT;
		while (randomY == playerY) {
			randomY = rand() % MAZE_HEIGHT;
		}

		randomX = MAZE_OFFSET + (randomX * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		randomY = MAZE_OFFSET + (randomY * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		enemies.push_back(new Spinner(randomX, randomY, renderer));
	}

	int patrollers = (level / 3);
	for (int i = 0; i < patrollers; i++) {
		int randomX = rand() % MAZE_WIDTH;
		while (randomX == playerX) {
			randomX = rand() % MAZE_WIDTH;
		}

		int randomY = rand() % MAZE_HEIGHT;
		while (randomY == playerY) {
			randomY = rand() % MAZE_HEIGHT;
		}

		randomX = MAZE_OFFSET + (randomX * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		randomY = MAZE_OFFSET + (randomY * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		enemies.push_back(new Patroller(randomX, randomY, renderer));
	}

	int roamers = (level / 4);
	for (int i = 0; i < roamers; i++) {
		int randomX = rand() % MAZE_WIDTH;
		while (randomX == playerX) {
			randomX = rand() % MAZE_WIDTH;
		}

		int randomY = rand() % MAZE_HEIGHT;
		while (randomY == playerY) {
			randomY = rand() % MAZE_HEIGHT;
		}

		randomX = MAZE_OFFSET + (randomX * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		randomY = MAZE_OFFSET + (randomY * WALL_LENGTH) + ((WALL_LENGTH - ENEMY_SIZE) / 2);
		enemies.push_back(new Roamer(randomX, randomY, renderer));
	}
}

EnemyController::~EnemyController() {
	for (auto enemy : enemies) {
		delete enemy;
	}
}

void EnemyController::UpdateEnemies(Maze* maze, SDL_Renderer* renderer, EnemyController* enemyController, Score* score, int playerX, int playerY, bool& isRunning) {
	for (auto enemy : enemies) {
		enemy->Move(maze);
		enemy->Shoot();
		enemy->Render(renderer);
		enemy->RenderLasers(renderer, maze, enemyController, score, playerX, playerY, isRunning);
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