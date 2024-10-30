#pragma once
#include "Enemy.h"
class Patroller : public Enemy
{
public:
	Patroller(int x, int y, SDL_Renderer* renderer) : Enemy(x, y, 3000, "patroller.png", renderer), moveSpeed(1) {};
	void Move(Maze* maze) override;
private:
	int moveSpeed;
};

