#include "Game.h"
#include <iostream>

Game::Game() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Space Escapee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        exit(1);
    }

	player = new Player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    playerTexture = IMG_LoadTexture(renderer, "player_sprite.png");

    if (!playerTexture) {
        exit(1);
    }

    title = IMG_LoadTexture(renderer, "title.png");

    if (!title) {
        exit(1);
    }

    maze = new Maze(renderer);
    portal = new Portal(renderer);
    timer = new Timer(renderer);
    score = new Score(renderer);
    level = new Level(renderer);
}

Game::~Game() {
    delete player;
    delete maze;
    delete portal;
    delete timer;
    delete score;
    SDL_DestroyTexture(playerTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    IMG_Quit();
	SDL_Quit();
}

void Game::Run() {
	while (true) {
		Input();
        CheckExit();
		Render();
	}
}

void Game::Input() {
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
    }

    if (state[SDL_SCANCODE_W]) {
        player->MoveUp(maze);
    }
    else if (state[SDL_SCANCODE_S]) {
        player->MoveDown(maze);
    }
    else if (state[SDL_SCANCODE_A]) {
        player->MoveLeft(maze);
    }
    else if (state[SDL_SCANCODE_D]) {
        player->MoveRight(maze);
    }

    if (state[SDL_SCANCODE_SPACE]) {
        player->Shoot();
    }

    if (state[SDL_SCANCODE_X]) {
        SDL_Quit();
        exit(0);
    }
}

void Game::CheckExit() {
    if ((player->getX() + (PLAYER_SIZE / 2)) > portal->getX() && (player->getX() + (PLAYER_SIZE / 2)) < (portal->getX() + PORTAL_WIDTH)) {
        if ((player->getY() + (PLAYER_SIZE / 2)) > portal->getY() && (player->getY() + (PLAYER_SIZE / 2)) < (portal->getY() + PORTAL_HEIGHT)) {
            LevelComplete();
        }
    }
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

    SDL_Rect titleRect = { (WINDOW_WIDTH / 2) - 100, 0, 200, 100 };
    SDL_RenderCopyEx(renderer, title, NULL, &titleRect, 0, NULL, SDL_FLIP_NONE);

    maze->Render(renderer);
    portal->Render(renderer);
    timer->Render(renderer);
    score->Render(renderer);
    level->Render(renderer);
    player->RenderLasers(renderer, maze);

    SDL_Rect playerRect = { player->getX(), player->getY(), PLAYER_SIZE, PLAYER_SIZE };
    float angle = player->getAngle();
    SDL_RenderCopyEx(renderer, playerTexture, NULL, &playerRect, angle, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void Game::LevelComplete() {
    delete maze;
    delete portal;
    maze = new Maze(renderer);
    portal = new Portal(renderer);


    timer->AddTime();
    score->AddScore(LEVEL_COMPLETE_SCORE);
    level->NextLevel();
}