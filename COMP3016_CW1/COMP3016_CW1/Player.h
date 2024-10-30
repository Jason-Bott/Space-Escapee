#pragma once
#include "Constants.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Maze.h"
#include "Laser.h"
#include "Score.h"

class Player
{
public:
	Player(int x, int y, SDL_Renderer* renderer);
	~Player();
	void MoveUp(Maze* maze);
	void MoveLeft(Maze* maze);
	void MoveDown(Maze* maze);
	void MoveRight(Maze* maze);
	void Shoot();
	void Blink();
	void RenderLasers(SDL_Renderer* renderer, Maze* maze, EnemyController* enemyController, Score* score);
	void RenderBlinkCooldown(SDL_Renderer* renderer);
	int getX() const { return x; }
	int getY() const { return y; }
	float getAngle() const { return angle; }
private:
	int x;
	int y;
	float angle;
	Laser* lasers[PLAYER_SHOTS];
	Mix_Chunk* laserSFX;
	Mix_Chunk* blinkSFX;
	int lastShotTime;
	int lastBlinkTime;
	SDL_Texture* numberTextures[10];
	SDL_Texture* blinkText;
	SDL_Texture* readyText;
};

