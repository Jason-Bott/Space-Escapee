#include "Portal.h"
#include "Constants.h"
#include "SDL_image.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Portal::Portal(SDL_Renderer* renderer, int playerX, int playerY) {
	srand(static_cast<unsigned>(time(0)));

	int randomX = rand() % MAZE_WIDTH;
	while (randomX == playerX) {
		randomX = rand() % MAZE_WIDTH;
	}
	x = randomX;

	int randomY = rand() % MAZE_HEIGHT;
	while (randomY == playerY) {
		randomY = rand() % MAZE_HEIGHT;
	}
	y = randomY;

	xPosition = ((x * WALL_LENGTH) + MAZE_OFFSET) + ((((WALL_LENGTH - WALL_WIDTH) - PORTAL_WIDTH) / 2) + WALL_WIDTH);
	yPosition = ((y * WALL_LENGTH) + MAZE_OFFSET) + ((((WALL_LENGTH - WALL_WIDTH) - PORTAL_HEIGHT) / 2) + WALL_WIDTH);

	portalTexture = IMG_LoadTexture(renderer, "portal_sprite.png");
	if (!portalTexture) {
		std::cout << "Failed to load texture: " << IMG_GetError() << std::endl;
		exit(1);
	}
}

Portal::~Portal() {
	if (portalTexture) {
		SDL_DestroyTexture(portalTexture);
		portalTexture = nullptr;
	}
}

void Portal::Render(SDL_Renderer* renderer) {
	SDL_Rect portalRect = { xPosition, yPosition, PORTAL_WIDTH, PORTAL_HEIGHT };
	SDL_RenderCopyEx(renderer, portalTexture, NULL, &portalRect, 0, NULL, SDL_FLIP_NONE);
}