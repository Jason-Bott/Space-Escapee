#include "Level.h"
#include "SDL_image.h"

Level::Level(SDL_Renderer* renderer) : level(1) {
	levelText = IMG_LoadTexture(renderer, "level_text.png");

	if (!levelText) {
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

Level::~Level() {
	if (levelText) {
		SDL_DestroyTexture(levelText);
		levelText = nullptr;
	}

	for (int i = 0; i < 10; ++i) {
		if (numberTextures[i]) {
			SDL_DestroyTexture(numberTextures[i]);
			numberTextures[i] = nullptr;
		}
	}
}

void Level::NextLevel() {
	level++;
}

std::vector<int> Level::LevelAsDigits() {
	std::vector<int> digits;
	int levelCopy = level;

	do {
		digits.push_back(levelCopy % 10);
		levelCopy /= 10;
	} while (levelCopy > 0);


	std::reverse(digits.begin(), digits.end());

	return digits;
}

void Level::Render(SDL_Renderer* renderer) {
	SDL_Rect levelRect = { 620, 1125, 120, 50 };
	SDL_RenderCopyEx(renderer, levelText, NULL, &levelRect, 0, NULL, SDL_FLIP_NONE);

	std::vector<int> digits = LevelAsDigits();

	for (int i = 0; i < digits.size(); i++) {
		int digit = digits[i];

		SDL_Rect numberRect = { 740 + (20 * i), 1125, 20, 50 };
		SDL_RenderCopyEx(renderer, numberTextures[digit], NULL, &numberRect, 0, NULL, SDL_FLIP_NONE);
	}
}