#include "Maze.h"
#include "SDL_image.h"
#include <cstdlib>
#include <ctime>

Maze::Maze(SDL_Renderer* renderer) {
	srand(static_cast<unsigned>(time(0)));
	wallTexture = IMG_LoadTexture(renderer, "wall_sprite.png");

	if (!wallTexture) {
		exit(1);
	}

	for (int x = 0; x < MAZE_WIDTH; x++) {
		for (int y = 0; y < MAZE_HEIGHT + 1; y++) {
			if (y == 0 || y == MAZE_HEIGHT) {
				horizontalWalls[x][y] = true;
			}
			else {
				int randomNum = rand() % 101;

				if (randomNum > 70) {
					horizontalWalls[x][y] = true;
				}
			}
		}
	}

	for (int x = 0; x < MAZE_WIDTH + 1; x++) {
		for (int y = 0; y < MAZE_HEIGHT; y++) {
			if (x == 0 || x == MAZE_WIDTH) {
				verticalWalls[x][y] = true;
			}
			else {
				int randomNum = rand() % 101;

				if (randomNum > 70) {
					if ((horizontalWalls[x - 1][y] == false || horizontalWalls[x - 1][y + 1] == false) && (horizontalWalls[x][y] == false || horizontalWalls[x][y + 1] == false)) {
						verticalWalls[x][y] = true;
					}
				}
			}
		}
	}
}

Maze::~Maze() {
	if (wallTexture) {
		SDL_DestroyTexture(wallTexture);
		wallTexture = nullptr;
	}
}

void Maze::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int x = 0; x < MAZE_WIDTH; x++) {
		for (int y = 0; y < MAZE_HEIGHT + 1; y++) {
			if (horizontalWalls[x][y] == true) {
				SDL_Rect wallRect = { (x * WALL_LENGTH) + MAZE_OFFSET, (y * WALL_LENGTH) + MAZE_OFFSET, WALL_LENGTH + WALL_WIDTH, WALL_WIDTH };
				SDL_RenderCopyEx(renderer, wallTexture, NULL, &wallRect, 0, NULL, SDL_FLIP_NONE);
			}
		}
	}

	for (int x = 0; x < MAZE_WIDTH + 1; x++) {
		for (int y = 0; y < MAZE_HEIGHT; y++) {
			if (verticalWalls[x][y] == true) {
				SDL_Rect wallRect = { (x * WALL_LENGTH) + MAZE_OFFSET, (y * WALL_LENGTH) + MAZE_OFFSET, WALL_WIDTH, WALL_LENGTH };
				SDL_RenderCopyEx(renderer, wallTexture, NULL, &wallRect, 0, NULL, SDL_FLIP_NONE);
			}
		}
	}
}

bool Maze::getHorizontalWall(int x, int y) {
	return horizontalWalls[x][y];
}

bool Maze::getVerticalWall(int x, int y) {
	return verticalWalls[x][y];
}