#pragma once
#include "SDL.h"

class Portal
{
public:
	Portal();
	void Render(SDL_Renderer* renderer);
	int getX() const { return xPosition; }
	int getY() const { return yPosition; }
private:
	int x;
	int y;
	int xPosition;
	int yPosition;
	SDL_Texture* portalTexture;
};

