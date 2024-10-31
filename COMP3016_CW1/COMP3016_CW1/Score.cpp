#include "Score.h"
#include "SDL_image.h"

Score::Score(SDL_Renderer* renderer) : score(0) {
	scoreText = IMG_LoadTexture(renderer, "score_text.png");

	if (!scoreText) {
		std::cout << "Failed to load texture: " << IMG_GetError() << std::endl;
		exit(1);
	}

	const char* filenames[] = {
		"number_0.png", "number_1.png", "number_2.png", "number_3.png", "number_4.png",
		"number_5.png", "number_6.png", "number_7.png", "number_8.png", "number_9.png"
	};

	for (int i = 0; i < 10; i++) {
		numberTextures[i] = IMG_LoadTexture(renderer, filenames[i]);

		if (!numberTextures[i]) {
			std::cout << "Failed to load texture: " << IMG_GetError() << std::endl;
			exit(1);
		}
	}
}

Score::~Score() {
	if (scoreText) {
		SDL_DestroyTexture(scoreText);
		scoreText = nullptr;
	}

	for (int i = 0; i < 10; ++i) {
		if (numberTextures[i]) {
			SDL_DestroyTexture(numberTextures[i]);
			numberTextures[i] = nullptr;
		}
	}
}

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
	SDL_Rect scoreRect = { 220, 50, 120, 50 };
	SDL_RenderCopyEx(renderer, scoreText, NULL, &scoreRect, 0, NULL, SDL_FLIP_NONE);

	std::vector<int> digits = ScoreAsDigits();

	for (int i = 0; i < digits.size(); i++) {
		int digit = digits[i];

		SDL_Rect numberRect = { 340 + (20 * i), 50, 20, 50 };
		SDL_RenderCopyEx(renderer, numberTextures[digit], NULL, &numberRect, 0, NULL, SDL_FLIP_NONE);
	}
}