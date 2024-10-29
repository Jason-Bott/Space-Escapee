#include "Laser.h"
#include "EnemyController.h"

void Laser::Move(Maze* maze, bool& shouldDestroy) {
	if (angle == 0) {
		if (y <= MAZE_OFFSET) {
			shouldDestroy = true;
			return;
		}

		int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
		int rightX = ((x + LASER_WIDTH) - MAZE_OFFSET) / WALL_LENGTH;
		int currentY = (y - MAZE_OFFSET) / WALL_LENGTH;
		int newY = ((y - LASER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

		if (newY == currentY) {
			y -= LASER_SPEED;
		}
		else {
			bool leftWall = maze->getHorizontalWall(leftX, currentY);
			bool rightWall = maze->getHorizontalWall(rightX, currentY);
			if (leftWall || rightWall) {
				shouldDestroy = true;
			}
			else {
				y -= LASER_SPEED;
			}
		}
	}
	else if (angle == 90) {
		if (x >= MAZE_OFFSET + (MAZE_WIDTH * WALL_LENGTH)) {
			shouldDestroy = true;
			return;
		}

		int currentX = ((x + LASER_WIDTH) - MAZE_OFFSET) / WALL_LENGTH;
		int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
		int bottomY = ((y + LASER_WIDTH) - MAZE_OFFSET) / WALL_LENGTH;
		int newX = (((x + LASER_WIDTH) + LASER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

		if (newX == currentX) {
			x += LASER_SPEED;
		}
		else {
			bool topWall = maze->getVerticalWall(newX, topY);
			bool bottomWall = maze->getVerticalWall(newX, bottomY);
			if (topWall || bottomWall) {
				shouldDestroy = true;
			}
			else {
				x += LASER_SPEED;
			}
		}
	}
	else if (angle == 180) {
		if (y >= MAZE_OFFSET + (MAZE_HEIGHT * WALL_LENGTH)) {
			shouldDestroy = true;
			return;
		}

		int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
		int rightX = ((x + LASER_WIDTH) - MAZE_OFFSET) / WALL_LENGTH;
		int currentY = ((y + LASER_WIDTH) - MAZE_OFFSET) / WALL_LENGTH;
		int newY = (((y + LASER_WIDTH) + LASER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

		if (newY == currentY) {
			y += LASER_SPEED;
		}
		else {
			bool leftWall = maze->getHorizontalWall(leftX, newY);
			bool rightWall = maze->getHorizontalWall(rightX, newY);
			if (leftWall || rightWall) {
				shouldDestroy = true;
			}
			else {
				y += LASER_SPEED;
			}
		}
	}
	else if (angle == 270) {
		if (x <= MAZE_OFFSET) {
			shouldDestroy = true;
			return;
		}

		int currentX = (x - MAZE_OFFSET) / WALL_LENGTH;
		int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
		int bottomY = ((y + LASER_WIDTH) - MAZE_OFFSET) / WALL_LENGTH;
		int newX = ((x - LASER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

		if (newX == currentX) {
			x -= LASER_SPEED;
		}
		else {
			bool topWall = maze->getVerticalWall(currentX, topY);
			bool bottomWall = maze->getVerticalWall(currentX, bottomY);
			if (topWall || bottomWall) {
				shouldDestroy = true;
			}
			else {
				x -= LASER_SPEED;
			}
		}
	}
}

void Laser::CheckForEnemies(EnemyController* enemyController, bool& shouldDestroy) {
	if (angle == 0) {
		enemyController->LaserCheck(x + (LASER_WIDTH / 2), y, shouldDestroy);
	}
	else if (angle == 90) {
		enemyController->LaserCheck(x + LASER_LENGTH, y + (LASER_WIDTH / 2), shouldDestroy);
	}
	else if (angle == 180) {
		enemyController->LaserCheck(x + (LASER_WIDTH / 2), y + LASER_LENGTH, shouldDestroy);
	}
	else if (angle == 270) {
		enemyController->LaserCheck(x, y + (LASER_WIDTH / 2), shouldDestroy);
	}
}

void Laser::CheckForPlayer() {

}