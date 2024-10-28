#include "Spinner.h"

void Spinner::Move(Maze* maze) {
	int currentTime = SDL_GetTicks();

	if (currentTime - lastSpin >= 2000) {
		if (angle == 270) {
			angle = 0;
		}
		else {
			angle += 90;
		}

		lastSpin = currentTime;
	}
}