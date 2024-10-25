#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Constants.h"
#include "Player.h"
#include "Maze.h"
#include "Portal.h"
#include "Timer.h"
#include "Score.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	void Input();
	void CheckExit();
	void Render();
	void LevelComplete();
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player;
	SDL_Texture* playerTexture;
	Maze* maze;
	Portal* portal;
	Timer* timer;
	Score* score;
};