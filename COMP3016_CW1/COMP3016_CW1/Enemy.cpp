#include "Enemy.h"
#include "SDL_image.h"

Enemy::Enemy(int x, int y, int fireRate, const char* spriteFile, SDL_Renderer* renderer) : x(x), y(y), angle(0), fireRate(fireRate), lastShotTime(0), lasers() {
	enemyTexture = IMG_LoadTexture(renderer, spriteFile);

	if (!enemyTexture) {
		exit(1);
	}

	for (int i = 0; i < ENEMY_SHOTS; i++) {
		lasers[i] = nullptr;
	}
}

Enemy::~Enemy() {
	if (enemyTexture) {
		SDL_DestroyTexture(enemyTexture);
		enemyTexture = nullptr;
	}
}

void Enemy::Shoot() {
	int currentTime = SDL_GetTicks();

	if (currentTime - lastShotTime >= fireRate) {
		for (int i = 0; i < ENEMY_SHOTS; i++) {
			if (lasers[i] == nullptr) {
				int laserX = 0;
				int laserY = 0;

				if (angle == 0) {
					laserX = x + (ENEMY_SIZE / 2) - 3;
					laserY = y;
				}
				else if (angle == 90) {
					laserX = x + ENEMY_SIZE - 8;
					laserY = y + (ENEMY_SIZE / 2) - 3;
				}
				else if (angle == 180) {
					laserX = x + (ENEMY_SIZE / 2) - 3;
					laserY = y + ENEMY_SIZE - 8;
				}
				else if (angle == 270) {
					laserX = x;
					laserY = y + (ENEMY_SIZE / 2) - 3;
				}

				lasers[i] = new Laser(laserX, laserY, angle);
				lastShotTime = currentTime;
				return;
			}
		}
	}
}

void Enemy::Render(SDL_Renderer* renderer) {
	SDL_Rect enemyRect = { x, y, ENEMY_SIZE, ENEMY_SIZE };
	SDL_RenderCopyEx(renderer, enemyTexture, NULL, &enemyRect, angle, NULL, SDL_FLIP_NONE);
}

void Enemy::RenderLasers(SDL_Renderer* renderer, Maze* maze) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	for (int i = 0; i < ENEMY_SHOTS; i++) {
		if (lasers[i] != nullptr) {
			bool shouldDestroy = false;
			lasers[i]->Move(maze, shouldDestroy);

			if (shouldDestroy) {
				delete lasers[i];
				lasers[i] = nullptr;
			}
			else if (lasers[i]->getAngle() == 0 || lasers[i]->getAngle() == 180) {
				SDL_Rect laserRect = { lasers[i]->getX(), lasers[i]->getY(), LASER_WIDTH, LASER_LENGTH };
				SDL_RenderFillRect(renderer, &laserRect);
			}
			else {
				SDL_Rect laserRect = { lasers[i]->getX(), lasers[i]->getY(), LASER_LENGTH, LASER_WIDTH };
				SDL_RenderFillRect(renderer, &laserRect);
			}
		}
	}
}