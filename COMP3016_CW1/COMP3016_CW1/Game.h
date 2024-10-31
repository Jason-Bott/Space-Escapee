#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Constants.h"
#include "Player.h"
#include "Maze.h"
#include "Portal.h"
#include "Timer.h"
#include "Score.h"
#include "Level.h"
#include "EnemyController.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
	void OnStart();
private:
	void Input();
	void CheckExit();
	void Render();
	void LevelComplete();
	void GameOver();
	void Restart();
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* menu;
	SDL_Texture* title;
	Player* player;
	SDL_Texture* playerTexture;
	Maze* maze;
	Portal* portal;
	Timer* timer;
	Score* score;
	Level* level;
	EnemyController* enemyController;
	SDL_Texture* gameOverText;
	SDL_Texture* pressToText;
	Mix_Music* music;
	Mix_Chunk* gameOverSFX;
	Mix_Chunk* portalSFX;
};