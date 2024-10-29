#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread> 

Game::Game() : isRunning(true) {
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

    gameOverText = IMG_LoadTexture(renderer, "game_over.png");

    if (!gameOverText) {
        exit(1);
    }

    maze = new Maze(renderer);
    portal = new Portal(renderer);
    timer = new Timer(renderer);
    score = new Score(renderer);
    level = new Level(renderer);
    enemyController = new EnemyController(renderer, level->getLevel());
}

Game::~Game() {
    delete player;
    delete maze;
    delete portal;
    delete timer;
    delete score;
    delete level;
    delete enemyController;
    SDL_DestroyTexture(playerTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    IMG_Quit();
	SDL_Quit();
}

void Game::Run() {
	while (isRunning) {
		Input();
        CheckExit();
		Render();
	}

    GameOver();
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
    enemyController->UpdateEnemies(maze, renderer, enemyController, score, player->getX(), player->getY(), isRunning);
    player->RenderLasers(renderer, maze, enemyController, score);

    SDL_Rect playerRect = { player->getX(), player->getY(), PLAYER_SIZE, PLAYER_SIZE };
    float angle = player->getAngle();
    SDL_RenderCopyEx(renderer, playerTexture, NULL, &playerRect, angle, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void Game::LevelComplete() {
    isRunning = false;
    return;

    delete maze;
    delete portal;
    delete enemyController;
    maze = new Maze(renderer);
    portal = new Portal(renderer);
    enemyController = new EnemyController(renderer, level->getLevel());

    timer->AddTime();
    score->AddScore(LEVEL_COMPLETE_SCORE);
    level->NextLevel();
}

void Game::GameOver() {
    SDL_Rect gameOverRect = { (WINDOW_WIDTH / 2) - 300, (WINDOW_HEIGHT / 2) - 100, 600, 200};
    SDL_RenderCopyEx(renderer, gameOverText, NULL, &gameOverRect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    bool waitingForInput = true;
    while (waitingForInput) {
        SDL_Event event;
        const Uint8* state = SDL_GetKeyboardState(NULL);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                exit(0);
            }
        }

        if (state[SDL_SCANCODE_ESCAPE]) {
            waitingForInput = false;
        }

        for (int key = 0; key < 512; key++) {
            if (state[key] && key != SDL_SCANCODE_ESCAPE) {
                Restart();
                waitingForInput = false;
                break;
            }
        }
    }
}

void Game::Restart() {
    isRunning = true;

    delete maze;
    delete portal;
    delete timer;
    delete score;
    delete level;
    delete enemyController;

    maze = new Maze(renderer);
    portal = new Portal(renderer);
    timer = new Timer(renderer);
    score = new Score(renderer);
    level = new Level(renderer);
    enemyController = new EnemyController(renderer, level->getLevel());

    Run();
}