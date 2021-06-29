#include "Game.h"

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(
            "Isometric Minesweeper",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            windowFlags
        );
        renderer = SDL_CreateRenderer(window, -1, 0);
        board = new Board(renderer);
        isRunning = true;
    } else {
        isRunning = false;
    }
}

Game::~Game()
{
    //dtor
}

void Game::mainLoop()
{
    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        handleEvents();
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                SDL_Quit();
                break;
            }
    }
}

void Game::update()
{

}

void Game::render()
{
    board->draw();

    SDL_RenderPresent(renderer);
}
