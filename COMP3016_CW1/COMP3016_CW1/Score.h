#pragma once
#include "Constants.h"
#include "SDL.h"
#include <iostream>
#include <vector>

class Score
{
public:
	Score() : score(0) {};
	void Render(SDL_Renderer* renderer);
	void AddScore(int amount);
	std::vector<int> ScoreAsDigits();
private:
	int score;
	SDL_Texture* scoreText;
	SDL_Texture* numberText;
};