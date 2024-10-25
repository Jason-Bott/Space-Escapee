#pragma once
#include "Constants.h"
#include "SDL.h"
#include <iostream>
#include <vector>

class Timer
{
public:
	Timer(SDL_Renderer* renderer);
	~Timer();
	void Render(SDL_Renderer* renderer);
	std::vector<int> CheckTime();
	void AddTime();
private:
	int time;
	int lastSecond;
	SDL_Texture* timeText;
	SDL_Texture* numberTextures[10];
};