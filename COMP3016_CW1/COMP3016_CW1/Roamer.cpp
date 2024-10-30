#include "Roamer.h"
#include <cstdlib>
#include <ctime>

void Roamer::Move(Maze* maze) {
	srand(static_cast<unsigned>(time(0)));
	int change = rand() % 3;

	if (angle == 0) {
		if (y == MAZE_OFFSET) {
			if (change == 0) {
				angle = 270;
			}
			else if (change == 1) {
				angle = 90;
			}
			else {
				angle = 180;
			}
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
				if (change == 0) {
					angle = 270;
				}
				else if (change == 1) {
					angle = 90;
				}
				else {
					angle = 180;
				}
			}
			else {
				y -= moveSpeed;
			}
		}
	}
	else if (angle == 90) {
		if (x == MAZE_OFFSET + (MAZE_WIDTH * WALL_LENGTH)) {
			if (change == 0) {
				angle = 270;
			}
			else if (change == 1) {
				angle = 0;
			}
			else {
				angle = 180;
			}
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
				if (change == 0) {
					angle = 270;
				}
				else if (change == 1) {
					angle = 0;
				}
				else {
					angle = 180;
				}
			}
			else {
				x += moveSpeed;
			}
		}
	}
	else if (angle == 180) {
		if (y == MAZE_OFFSET + (MAZE_HEIGHT * WALL_LENGTH)) {
			if (change == 0) {
				angle = 270;
			}
			else if (change == 1) {
				angle = 90;
			}
			else {
				angle = 0;
			}
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
				if (change == 0) {
					angle = 270;
				}
				else if (change == 1) {
					angle = 90;
				}
				else {
					angle = 0;
				}
			}
			else {
				y += moveSpeed;
			}
		}
	}
	else if (angle == 270) {
		if (x == MAZE_OFFSET) {
			if (change == 0) {
				angle = 0;
			}
			else if (change == 1) {
				angle = 90;
			}
			else {
				angle = 180;
			}
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
				if (change == 0) {
					angle = 0;
				}
				else if (change == 1) {
					angle = 90;
				}
				else {
					angle = 180;
				}
			}
			else {
				x -= moveSpeed;
			}
		}
	}
}