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
        board = new Board(renderer, offsetX, offsetY, rows, columns);

        // Set initial full mask
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                minefieldMask[y][x] = 1;
            }
        }

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

         case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            click(x, y);
    }
}

void Game::update()
{

}

void Game::render()
{
    board->draw(minefield, minefieldMask);

    SDL_RenderPresent(renderer);
}

void Game::click(int screenX, int screenY)
{
    int screenXwithOffset = screenX - offsetX;
    int screenYwithOffset = screenY - offsetY;

    Point clickedPoint2D = IsoConvert::isoToTwoD(screenXwithOffset, screenYwithOffset);
    clickedPoint2D.x = clickedPoint2D.x - (board->getMapTileScreenWidth() / 2);
    clickedPoint2D.y = clickedPoint2D.y + (board->getMapTileScreenHeight() / 2);

    int column = ceil(clickedPoint2D.x / board->getMapTileScreenWidth()) -1;
    int row = ceil(clickedPoint2D.y / board->getMapTileScreenHeight()) - 1;

    if (row < 0 || row >= rows) {
      return;
    }

    if (column < 0 || column >= columns) {
      return;
    }

    if (!gameStarted) {
        startGame();
    }

    minefieldMask[row][column] = 0;

    if (minefield[row][column] == mineMarker) {
        printf("GAME OVER"); // TODO: fancy text
        gameStarted = false;
    }

    printDebug();
}

void Game::startGame()
{
    // TODO: don't place mine on first clicked field

    // Clear minefield and it's mask
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            minefield[y][x] = 0;
            minefieldMask[y][x] = 1;
        }
    }

    // Place mines
    int minesLeftToPlace = numberOfMines;
    while (minesLeftToPlace > 0)
    {
        int x = rand() % columns;
        int y = rand() % rows;

        if (minefield[y][x] != mineMarker) {
            minefield[y][x] = mineMarker;
            minesLeftToPlace--;
        }
    }

    // Calculate number of adjacent mines
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (minefield[y][x] == mineMarker) {
              continue;
            }

            minefield[y][x] = 0;

            if (y > 0 && x > 0 && minefield[y-1][x-1] == mineMarker) {
                minefield[y][x]++;
            }

            if (y > 0 && minefield[y-1][x] == mineMarker) {
                minefield[y][x]++;
            }

            if (y > 0 && x < columns - 1 && minefield[y-1][x+1] == mineMarker) {
                minefield[y][x]++;
            }

            if (x > 0 && minefield[y][x-1] == mineMarker) {
                minefield[y][x]++;
            }

            if (x < columns - 1 && minefield[y][x+1] == mineMarker) {
                minefield[y][x]++;
            }

            if (y < rows - 1 && x > 0 && minefield[y+1][x-1] == mineMarker) {
                minefield[y][x]++;
            }

            if (y < rows - 1 && minefield[y+1][x] == mineMarker) {
                minefield[y][x]++;
            }

            if (y < rows - 1 && x < columns - 1 && minefield[y+1][x+1] == mineMarker) {
                minefield[y][x]++;
            }
        }
    }

    gameStarted = true;
}

void Game::printDebug()
{
    printf("MINEFILED:\n");
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (minefield[y][x] == mineMarker) {
              printf(" x");
            } else {
              printf("%2i", minefield[y][x] );
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("MINEFILED MASK:\n");
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            printf("%2i", minefieldMask[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
