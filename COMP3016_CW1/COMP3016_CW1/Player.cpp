#include "Player.h"
#include "SDL.h"
#include <iostream>

void Player::MoveUp(Maze* maze) {
	if (y == MAZE_OFFSET) {
		angle = 0;
		return;
	}

	int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
	int rightX = ((x + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int currentY = (y - MAZE_OFFSET) / WALL_LENGTH;
	int newY = ((y - PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newY == currentY) {
		y -= PLAYER_SPEED;
		angle = 0;
	}
	else {
		bool leftWall = maze->getHorizontalWall(leftX, currentY);
		bool rightWall = maze->getHorizontalWall(rightX, currentY);
		if (leftWall || rightWall) {
			angle = 0;
		}
		else {
			y -= PLAYER_SPEED;
			angle = 0;
		}
	}
}

void Player::MoveLeft(Maze* maze) {
	if (x == MAZE_OFFSET) {
		angle = 270;
		return;
	}

	int currentX = (x - MAZE_OFFSET) / WALL_LENGTH;
	int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
	int bottomY = ((y + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int newX = ((x - PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newX == currentX) {
		x -= PLAYER_SPEED;
		angle = 270;
	}
	else {
		bool topWall = maze->getVerticalWall(currentX, topY);
		bool bottomWall = maze->getVerticalWall(currentX, bottomY);
		if (topWall || bottomWall) {
			angle = 270;
		}
		else {
			x -= PLAYER_SPEED;
			angle = 270;
		}
	}
}

void Player::MoveDown(Maze* maze) {
	if (y == MAZE_OFFSET + (MAZE_HEIGHT * WALL_LENGTH)) {
		angle = 180;
		return;
	}

	int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
	int rightX = ((x + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int currentY = ((y + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int newY = (((y + PLAYER_SIZE) + PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newY == currentY) {
		y += PLAYER_SPEED;
		angle = 180;
	}
	else {
		bool leftWall = maze->getHorizontalWall(leftX, newY);
		bool rightWall = maze->getHorizontalWall(rightX, newY);
		if (leftWall || rightWall) {
			angle = 180;
		}
		else {
			y += PLAYER_SPEED;
			angle = 180;
		}
	}
}

void Player::MoveRight(Maze* maze) {
	if (x == MAZE_OFFSET + (MAZE_WIDTH * WALL_LENGTH)) {
		angle = 90;
		return;
	}

	int currentX = ((x + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
	int bottomY = ((y + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int newX = (((x + PLAYER_SIZE) + PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newX == currentX) {
		x += PLAYER_SPEED;
		angle = 90;
	}
	else {
		bool topWall = maze->getVerticalWall(newX, topY);
		bool bottomWall = maze->getVerticalWall(newX, bottomY);
		if (topWall || bottomWall) {
			angle = 90;
		}
		else {
			x += PLAYER_SPEED;
			angle = 90;
		}
	}
}

void Player::Shoot() {
	int currentTime = SDL_GetTicks();

	if (currentTime - lastShotTime >= SHOT_COOLDOWN) {
		for (int i = 0; i < PLAYER_SHOTS; i++) {
			if (lasers[i] == NULL) {
				int laserX = 0;
				int laserY = 0;

				if (angle == 0) {
					laserX = x + (PLAYER_SIZE / 2) - 3;
					laserY = y;
				}
				else if (angle == 90) {
					laserX = x + PLAYER_SIZE - 8;
					laserY = y + (PLAYER_SIZE / 2) - 3;
				}
				else if (angle == 180) {
					laserX = x + (PLAYER_SIZE / 2) - 3;
					laserY = y + PLAYER_SIZE - 8;
				}
				else if (angle == 270) {
					laserX = x;
					laserY = y + (PLAYER_SIZE / 2) - 3;
				}

				lasers[i] = new Laser(laserX, laserY, angle);
				lastShotTime = currentTime;
				return;
			}
		}
	}
}

void Player::RenderLasers(SDL_Renderer* renderer, Maze* maze) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	for (int i = 0; i < PLAYER_SHOTS; i++) {
		if (lasers[i] != NULL) {
			bool shouldDestroy = false;
			lasers[i]->Move(maze, shouldDestroy);

			if (shouldDestroy) {
				delete lasers[i];
				lasers[i] = NULL;
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