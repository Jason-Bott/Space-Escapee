#include "Patroller.h"

void Patroller::Move(Maze* maze) {
	if (angle == 0) {
		if (y == MAZE_OFFSET) {
			angle += 90;
			return;
		}

		int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
		int rightX = ((x + ENEMY_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
		int currentY = (y - MAZE_OFFSET) / WALL_LENGTH;
		int newY = ((y - moveSpeed) - MAZE_OFFSET) / WALL_LENGTH;

		if (newY == currentY) {
			y -= moveSpeed;
		}
		else {
			bool leftWall = maze->getHorizontalWall(leftX, currentY);
			bool rightWall = maze->getHorizontalWall(rightX, currentY);
			if (leftWall || rightWall) {
				angle += 90;
			}
			else {
				y -= moveSpeed;
			}
		}
	}
	else if (angle == 90) {
		if (x == MAZE_OFFSET + (MAZE_WIDTH * WALL_LENGTH)) {
			angle += 90;
			return;
		}

		int currentX = ((x + ENEMY_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
		int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
		int bottomY = ((y + ENEMY_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
		int newX = (((x + ENEMY_SIZE) + moveSpeed) - MAZE_OFFSET) / WALL_LENGTH;

		if (newX == currentX) {
			x += moveSpeed;
		}
		else {
			bool topWall = maze->getVerticalWall(newX, topY);
			bool bottomWall = maze->getVerticalWall(newX, bottomY);
			if (topWall || bottomWall) {
				angle += 90;
			}
			else {
				x += moveSpeed;
			}
		}
	}
	else if (angle == 180) {
		if (y == MAZE_OFFSET + (MAZE_HEIGHT * WALL_LENGTH)) {
			angle += 90;
			return;
		}

		int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
		int rightX = ((x + ENEMY_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
		int currentY = ((y + ENEMY_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
		int newY = (((y + ENEMY_SIZE) + moveSpeed) - MAZE_OFFSET) / WALL_LENGTH;

		if (newY == currentY) {
			y += moveSpeed;
		}
		else {
			bool leftWall = maze->getHorizontalWall(leftX, newY);
			bool rightWall = maze->getHorizontalWall(rightX, newY);
			if (leftWall || rightWall) {
				angle += 90;
			}
			else {
				y += moveSpeed;
			}
		}
	}
	else if (angle == 270) {
		if (x == MAZE_OFFSET) {
			angle = 0;
			return;
		}

		int currentX = (x - MAZE_OFFSET) / WALL_LENGTH;
		int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
		int bottomY = ((y + ENEMY_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
		int newX = ((x - moveSpeed) - MAZE_OFFSET) / WALL_LENGTH;

		if (newX == currentX) {
			x -= moveSpeed;
		}
		else {
			bool topWall = maze->getVerticalWall(currentX, topY);
			bool bottomWall = maze->getVerticalWall(currentX, bottomY);
			if (topWall || bottomWall) {
				angle = 0;
			}
			else {
				x -= moveSpeed;
			}
		}
	}
}