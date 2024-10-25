#include "Timer.h"
#include "SDL_image.h"

std::vector<int> Timer::CheckTime() {
	int currentTime = SDL_GetTicks();

	if (currentTime - lastSecond >= 1000) {
		time--;
		lastSecond = currentTime;
	}

	std::vector<int> digits;

	if (time < 0) {
		//End Game
	}

	if (time > 9999) {
		time = 9999;
	}

	int timeCopy = time;

	do {
		digits.push_back(timeCopy % 10);
		timeCopy /= 10;
	} while (timeCopy > 0);

	
	std::reverse(digits.begin(), digits.end());

	return digits;
}

void Timer::AddTime() {
	time += TIME_INCREASE;
}

void Timer::Render(SDL_Renderer* renderer) {
	std::vector<int> digits = CheckTime();

	timeText = IMG_LoadTexture(renderer, "time_text.png");

	if (!timeText) {
		exit(1);
	}

	SDL_Rect timeRect = { 0, 0, 100, 50 };
	SDL_RenderCopyEx(renderer, timeText, NULL, &timeRect, 0, NULL, SDL_FLIP_NONE);

	for (int i = 0; i < digits.size(); i++) {

		switch (digits[i]) {
			case 0:
				numberText = IMG_LoadTexture(renderer, "number_0.png");
				break;
			case 1:
				numberText = IMG_LoadTexture(renderer, "number_1.png");
				break;
			case 2:
				numberText = IMG_LoadTexture(renderer, "number_2.png");
				break;
			case 3:
				numberText = IMG_LoadTexture(renderer, "number_3.png");
				break;
			case 4:
				numberText = IMG_LoadTexture(renderer, "number_4.png");
				break;
			case 5:
				numberText = IMG_LoadTexture(renderer, "number_5.png");
				break;
			case 6:
				numberText = IMG_LoadTexture(renderer, "number_6.png");
				break;
			case 7:
				numberText = IMG_LoadTexture(renderer, "number_7.png");
				break;
			case 8:
				numberText = IMG_LoadTexture(renderer, "number_8.png");
				break;
			case 9:
				numberText = IMG_LoadTexture(renderer, "number_9.png");
				break;
		}

		SDL_Rect numberRect = { 100 + (20 * i), 0, 20, 50};
		SDL_RenderCopyEx(renderer, numberText, NULL, &numberRect, 0, NULL, SDL_FLIP_NONE);
	}
}