#pragma once
#include "SDL.h"
#include "Constants.h"

class Maze
{
public:
	Maze(SDL_Renderer* renderer);
	~Maze();
	void Render(SDL_Renderer* renderer);
	bool getHorizontalWall(int x, int y);
	bool getVerticalWall(int x, int y);
private:
	bool horizontalWalls[MAZE_WIDTH][MAZE_HEIGHT + 1] = { false };
	bool verticalWalls[MAZE_WIDTH + 1][MAZE_HEIGHT] = { false };
	SDL_Texture* wallTexture;
};