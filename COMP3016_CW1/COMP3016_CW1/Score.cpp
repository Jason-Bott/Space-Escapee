#include "Score.h"
#include "SDL_image.h"

void Score::AddScore(int amount) {
	score += amount;
}

std::vector<int> Score::ScoreAsDigits() {
	std::vector<int> digits;
	int scoreCopy = score;

	do {
		digits.push_back(scoreCopy % 10);
		scoreCopy /= 10;
	} while (scoreCopy > 0);


	std::reverse(digits.begin(), digits.end());

	return digits;
}

void Score::Render(SDL_Renderer* renderer) {
	scoreText = IMG_LoadTexture(renderer, "score_text.png");

	if (!scoreText) {
		exit(1);
	}

	SDL_Rect scoreRect = { 200, 0, 120, 50 };
	SDL_RenderCopyEx(renderer, scoreText, NULL, &scoreRect, 0, NULL, SDL_FLIP_NONE);

	std::vector<int> digits = ScoreAsDigits();

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

		SDL_Rect numberRect = { 320 + (20 * i), 0, 20, 50 };
		SDL_RenderCopyEx(renderer, numberText, NULL, &numberRect, 0, NULL, SDL_FLIP_NONE);
	}
}