#pragma once
#include "Constants.h"
#include "SDL.h"
#include <iostream>
#include <vector>

class Level
{
public:
	Level(SDL_Renderer* renderer);
	~Level();
	void Render(SDL_Renderer* renderer);
	void NextLevel();
	std::vector<int> LevelAsDigits();
private:
	int level;
	SDL_Texture* levelText;
	SDL_Texture* numberTextures[10];
};