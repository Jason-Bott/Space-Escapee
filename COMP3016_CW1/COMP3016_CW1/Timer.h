#pragma once
#include "Constants.h"
#include "SDL.h"
#include <iostream>
#include <vector>

class Timer
{
public:
	Timer() : time(START_TIME), lastSecond(0) {};
	void Render(SDL_Renderer* renderer);
	std::vector<int> CheckTime();
	void AddTime();
private:
	int time;
	int lastSecond;
	SDL_Texture* timeText;
	SDL_Texture* numberText;
};