#pragma once
#include "Constants.h"
#include "Maze.h"
#include "Laser.h"

class Player
{
public:
	Player(int x, int y) : x(x), y(y), angle(0), lasers(), lastShotTime(0) {
		for (int i = 0; i < PLAYER_SHOTS; i++) {
			lasers[i] = nullptr;
		}
	};
	~Player();
	void MoveUp(Maze* maze);
	void MoveLeft(Maze* maze);
	void MoveDown(Maze* maze);
	void MoveRight(Maze* maze);
	void Shoot();
	void RenderLasers(SDL_Renderer* renderer, Maze* maze);
	int getX() const { return x; }
	int getY() const { return y; }
	float getAngle() const { return angle; }
private:
	int x;
	int y;
	float angle;
	Laser* lasers[PLAYER_SHOTS];
	int lastShotTime;
};

