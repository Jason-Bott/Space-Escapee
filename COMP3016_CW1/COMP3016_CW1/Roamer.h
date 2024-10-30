#pragma once
#include "Enemy.h"
class Roamer : public Enemy
{
public:
	Roamer(int x, int y, SDL_Renderer* renderer) : Enemy(x, y, 3000, "roamer.png", renderer), moveSpeed(1) {};
	void Move(Maze* maze) override;
private:
	int moveSpeed;
};

