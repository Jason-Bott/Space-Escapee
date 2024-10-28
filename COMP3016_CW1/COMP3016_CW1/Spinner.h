#pragma once
#include "Enemy.h"
class Spinner : public Enemy
{
public:
	Spinner(int x, int y, SDL_Renderer* renderer) : Enemy(x, y, 2000, "spinner.png", renderer), lastSpin(-1000) {};
	void Move(Maze* maze) override;
private:
	int lastSpin;
};