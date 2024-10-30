#include "Player.h"
#include <iostream>

Player::Player(int x, int y, SDL_Renderer* renderer) : x(x), y(y), angle(0), lasers(), lastShotTime(0), lastBlinkTime(SDL_GetTicks() - BLINK_COOLDOWN) {
	for (int i = 0; i < PLAYER_SHOTS; i++) {
		lasers[i] = nullptr;
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

	blinkText = IMG_LoadTexture(renderer, "blink_text.png");
	if (!blinkText) {
		exit(1);
	}

	readyText = IMG_LoadTexture(renderer, "ready_text.png");
	if (!readyText) {
		exit(1);
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	laserSFX = Mix_LoadWAV("laser.mp3");
	if (!laserSFX) {
		exit(1);
	}

	blinkSFX = Mix_LoadWAV("blinkSFX.mp3");
	if (!blinkSFX) {
		exit(1);
	}
};

Player::~Player() {
	for (int i = 0; i < PLAYER_SHOTS; i++) {
		if (lasers[i] != nullptr) {
			delete lasers[i];
			lasers[i] = nullptr;
		}
	}

	if (blinkText) {
		SDL_DestroyTexture(blinkText);
		blinkText = nullptr;
	}

	if (readyText) {
		SDL_DestroyTexture(readyText);
		readyText = nullptr;
	}

	for (int i = 0; i < 10; ++i) {
		if (numberTextures[i]) {
			SDL_DestroyTexture(numberTextures[i]);
			numberTextures[i] = nullptr;
		}
	}
}

void Player::MoveUp(Maze* maze) {
	if (y == MAZE_OFFSET) {
		angle = 0;
		return;
	}

	int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
	int rightX = ((x + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int currentY = (y - MAZE_OFFSET) / WALL_LENGTH;
	int newY = ((y - PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newY == currentY) {
		y -= PLAYER_SPEED;
		angle = 0;
	}
	else {
		bool leftWall = maze->getHorizontalWall(leftX, currentY);
		bool rightWall = maze->getHorizontalWall(rightX, currentY);
		if (leftWall || rightWall) {
			angle = 0;
		}
		else {
			y -= PLAYER_SPEED;
			angle = 0;
		}
	}
}

void Player::MoveLeft(Maze* maze) {
	if (x == MAZE_OFFSET) {
		angle = 270;
		return;
	}

	int currentX = (x - MAZE_OFFSET) / WALL_LENGTH;
	int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
	int bottomY = ((y + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int newX = ((x - PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newX == currentX) {
		x -= PLAYER_SPEED;
		angle = 270;
	}
	else {
		bool topWall = maze->getVerticalWall(currentX, topY);
		bool bottomWall = maze->getVerticalWall(currentX, bottomY);
		if (topWall || bottomWall) {
			angle = 270;
		}
		else {
			x -= PLAYER_SPEED;
			angle = 270;
		}
	}
}

void Player::MoveDown(Maze* maze) {
	if (y == MAZE_OFFSET + (MAZE_HEIGHT * WALL_LENGTH)) {
		angle = 180;
		return;
	}

	int leftX = (x - MAZE_OFFSET) / WALL_LENGTH;
	int rightX = ((x + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int currentY = ((y + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int newY = (((y + PLAYER_SIZE) + PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newY == currentY) {
		y += PLAYER_SPEED;
		angle = 180;
	}
	else {
		bool leftWall = maze->getHorizontalWall(leftX, newY);
		bool rightWall = maze->getHorizontalWall(rightX, newY);
		if (leftWall || rightWall) {
			angle = 180;
		}
		else {
			y += PLAYER_SPEED;
			angle = 180;
		}
	}
}

void Player::MoveRight(Maze* maze) {
	if (x == MAZE_OFFSET + (MAZE_WIDTH * WALL_LENGTH)) {
		angle = 90;
		return;
	}

	int currentX = ((x + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int topY = (y - MAZE_OFFSET) / WALL_LENGTH;
	int bottomY = ((y + PLAYER_SIZE) - MAZE_OFFSET) / WALL_LENGTH;
	int newX = (((x + PLAYER_SIZE) + PLAYER_SPEED) - MAZE_OFFSET) / WALL_LENGTH;

	if (newX == currentX) {
		x += PLAYER_SPEED;
		angle = 90;
	}
	else {
		bool topWall = maze->getVerticalWall(newX, topY);
		bool bottomWall = maze->getVerticalWall(newX, bottomY);
		if (topWall || bottomWall) {
			angle = 90;
		}
		else {
			x += PLAYER_SPEED;
			angle = 90;
		}
	}
}

void Player::Blink() {
	int currentTime = SDL_GetTicks();

	if (currentTime - lastBlinkTime >= BLINK_COOLDOWN) {
		if (angle == 0) {
			y -= WALL_LENGTH;
		}
		else if (angle == 90) {
			x += WALL_LENGTH;
		}
		else if (angle == 180) {
			y += WALL_LENGTH;
		}
		else if (angle == 270) {
			x -= WALL_LENGTH;
		}

		Mix_PlayChannel(-1, blinkSFX, 0);
		lastBlinkTime = currentTime;
	}
}

void Player::Shoot() {
	int currentTime = SDL_GetTicks();

	if (currentTime - lastShotTime >= SHOT_COOLDOWN) {
		for (int i = 0; i < PLAYER_SHOTS; i++) {
			if (lasers[i] == nullptr) {
				int laserX = 0;
				int laserY = 0;

				if (angle == 0) {
					laserX = x + (PLAYER_SIZE / 2) - 3;
					laserY = y;
				}
				else if (angle == 90) {
					laserX = x + PLAYER_SIZE - 8;
					laserY = y + (PLAYER_SIZE / 2) - 3;
				}
				else if (angle == 180) {
					laserX = x + (PLAYER_SIZE / 2) - 3;
					laserY = y + PLAYER_SIZE - 8;
				}
				else if (angle == 270) {
					laserX = x;
					laserY = y + (PLAYER_SIZE / 2) - 3;
				}

				lasers[i] = new Laser(laserX, laserY, angle);
				lastShotTime = currentTime;

				Mix_PlayChannel(-1, laserSFX, 0);
				return;
			}
		}
	}
}

void Player::RenderLasers(SDL_Renderer* renderer, Maze* maze, EnemyController* enemyController, Score* score) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	for (int i = 0; i < PLAYER_SHOTS; i++) {
		if (lasers[i] != nullptr) {
			bool shouldDestroy = false;
			lasers[i]->Move(maze, shouldDestroy);

			if (shouldDestroy) {
				delete lasers[i];
				lasers[i] = nullptr;
			}
			else {
				lasers[i]->CheckForEnemies(enemyController, shouldDestroy);

				if (shouldDestroy) {
					delete lasers[i];
					lasers[i] = nullptr;
					score->AddScore(ENEMY_DEFEAT_SCORE);
				}
				else if (lasers[i]->getAngle() == 0 || lasers[i]->getAngle() == 180) {
					SDL_Rect laserRect = { lasers[i]->getX(), lasers[i]->getY(), LASER_WIDTH, LASER_LENGTH };
					SDL_RenderFillRect(renderer, &laserRect);
				}
				else {
					SDL_Rect laserRect = { lasers[i]->getX(), lasers[i]->getY(), LASER_LENGTH, LASER_WIDTH };
					SDL_RenderFillRect(renderer, &laserRect);
				}
			}
		}
	}
}

void Player::RenderBlinkCooldown(SDL_Renderer* renderer) {
	SDL_Rect blinkRect = { 120, 1125, 120, 50 };
	SDL_RenderCopyEx(renderer, blinkText, NULL, &blinkRect, 0, NULL, SDL_FLIP_NONE);

	std::vector<int> digits;
	int timeLeft = BLINK_COOLDOWN - (SDL_GetTicks() - lastBlinkTime);

	if (timeLeft <= 0) {
		SDL_Rect readyRect = { 240, 1125, 120, 50 };
		SDL_RenderCopyEx(renderer, readyText, NULL, &readyRect, 0, NULL, SDL_FLIP_NONE);
		return;
	}

	timeLeft = (timeLeft / 1000) + 1;

	do {
		digits.push_back(timeLeft % 10);
		timeLeft /= 10;
	} while (timeLeft > 0);


	std::reverse(digits.begin(), digits.end());

	for (int i = 0; i < digits.size(); i++) {
		int digit = digits[i];

		SDL_Rect numberRect = { 240 + (20 * i), 1125, 20, 50 };
		SDL_RenderCopyEx(renderer, numberTextures[digit], NULL, &numberRect, 0, NULL, SDL_FLIP_NONE);
	}
}