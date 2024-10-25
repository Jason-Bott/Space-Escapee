#include "Timer.h"
#include "SDL_image.h"

Timer::Timer(SDL_Renderer* renderer) : time(START_TIME), lastSecond(0) {
	timeText = IMG_LoadTexture(renderer, "time_text.png");

	if (!timeText) {
		exit(1);
	}

	const char* filenames[] = {
		"number_0.png", "number_1.png", "number_2.png", "number_3.png", "number_4.png",
		"number_5.png", "number_6.png", "number_7.png", "number_8.png", "number_9.png"
	};

	for (int i = 0; i < 10; i++) {
		numberTextures[i] = IMG_LoadTexture(renderer, filenames[i]);
		
		if (!numberTextures[i]) {
			exit(1);
		}
	}
}

Timer::~Timer() {
	if (timeText) {
		SDL_DestroyTexture(timeText);
		timeText = nullptr;
	}

	for (int i = 0; i < 10; ++i) {
		if (numberTextures[i]) {
			SDL_DestroyTexture(numberTextures[i]);
			numberTextures[i] = nullptr;
		}
	}
}

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

	SDL_Rect timeRect = { 0, 0, 100, 50 };
	SDL_RenderCopyEx(renderer, timeText, NULL, &timeRect, 0, NULL, SDL_FLIP_NONE);

	for (int i = 0; i < digits.size(); i++) {
		int digit = digits[i];

		SDL_Rect numberRect = { 100 + (20 * i), 0, 20, 50 };
		SDL_RenderCopyEx(renderer, numberTextures[digit], NULL, &numberRect, 0, NULL, SDL_FLIP_NONE);
	}
}