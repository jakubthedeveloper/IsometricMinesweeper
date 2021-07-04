#include "Game.h"

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        isoConvert = new IsoConvert();
        window = SDL_CreateWindow(
            "Isometric Minesweeper",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            windowFlags
        );
        renderer = SDL_CreateRenderer(window, -1, 0);
        textureLoader = new TextureLoader(renderer);

        board = new Board(
            renderer,
            textureLoader,
            offsetX,
            offsetY,
            rows,
            columns,
            isoConvert
        );
        gui = new Gui(renderer, textureLoader);
        mousePoint = new Point(0, 0);
        currentField = new Field(-1, -1);
        board->highlight = currentField;
        maskAll();

        isRunning = true;
    } else {
        isRunning = false;
    }
}

Game::~Game()
{

}

void Game::mainLoop()
{
    while (isRunning)
    {
        handleEvents();
        update();
        render();
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

        case SDL_MOUSEMOTION:
            // TODO: check Left/Right/Both mouse buttons
            int x, y;
            SDL_GetMouseState(&x, &y);
            mousePoint->x = x;
            mousePoint->y = y;
            isoConvert->pointToField(
                mousePoint,
                currentField,
                offsetX,
                offsetY,
                board->getMapTileScreenWidth(),
                board->getMapTileScreenHeight()
            );
            break;

        case SDL_MOUSEBUTTONDOWN:
            clickField(currentField);
    }
}

void Game::update()
{

}

void Game::render()
{
    board->draw(minefield, minefieldMask);

    if (gameOver) {
        if (won) {
            gui->drawYouWon();
        } else {
            gui->drawYouLoose();
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::clickField(Field *field)
{
    if (gameOver) {
        maskAll();
        gameOver = false;
        gameStarted = false;
        won = false;

        return;
    }

    if (field->y < 0 || field->y >= rows) {
        return;
    }

    if (field->x < 0 || field->x >= columns) {
        return;
    }

    if (!gameStarted) {
        startGame(field);
    }

    minefieldMask[field->y][field->x] = 0;

    if (minefield[field->y][field->x] == mineMarker) {
        minefield[field->y][field->x] = boomMarker;
        uncoverAll();
        gameStarted = false;
        gameOver = true;
        return;
    }

    if (minefield[field->y][field->x] == 0) {
        // Uncover zeros
        bool uncovered = false;
        do {
            uncovered = false;
            for (int y = 0; y < rows; y++) {
                for (int x = 0; x < columns; x++) {
                    if (minefield[y][x] != 0 || minefieldMask[y][x] != 0) {
                        continue;
                    }

                    // X, Y - 1
                    if (y > 0 && minefield[y-1][x] == 0 && minefieldMask[y-1][x] == 1) {
                        minefieldMask[y-1][x] = 0;
                        uncoverNumbersAround(x, y-1);
                        uncovered = true;
                    }

                    // X - 1, Y - 1
                    if (x > 0 && minefield[y][x-1] == 0 && y > 0 && minefield[y-1][x-1] == 0 && minefieldMask[y-1][x-1] == 1) {
                        minefieldMask[y-1][x-1] = 0;
                        uncoverNumbersAround(x-1, y-1);
                        uncovered = true;
                    }

                    // X + 1, Y - 1
                    if (x < columns - 1 && y > 0 && minefield[y-1][x+1] == 0 && minefieldMask[y-1][x+1] == 1) {
                        minefieldMask[y-1][x+1] = 0;
                        uncoverNumbersAround(x+1, y-1);
                        uncovered = true;
                    }

                    // X - 1, Y
                    if (x > 0 && minefield[y][x-1] == 0 && minefieldMask[y][x-1] == 1) {
                        minefieldMask[y][x-1] = 0;
                        uncoverNumbersAround(x-1, y);
                        uncovered = true;
                    }

                    // X + 1, Y
                    if (x < columns - 1 && minefield[y][x+1] == 0 && minefieldMask[y][x+1] == 1) {
                        minefieldMask[y][x+1] = 0;
                        uncoverNumbersAround(x+1, y);
                        uncovered = true;
                    }

                    // X, Y + 1
                    if (y < rows - 1 && minefield[y+1][x] == 0 && minefieldMask[y+1][x] == 1) {
                        minefieldMask[y+1][x] = 0;
                        uncoverNumbersAround(x, y+1);
                        uncovered = true;
                    }

                    // X - 1, Y + 1
                    if (x > 0 && y < rows - 1 && minefield[y+1][x-1] == 0 && minefieldMask[y+1][x-1] == 1) {
                        minefieldMask[y+1][x-1] = 0;
                        uncoverNumbersAround(x-1, y+1);
                        uncovered = true;
                    }

                    // X + 1, Y + 1
                    if (y < rows - 1 && minefield[y+1][x+1] == 0 && minefieldMask[y+1][x+1] == 1) {
                        minefieldMask[y+1][x+1] = 0;
                        uncoverNumbersAround(x+1, y+1);
                        uncovered = true;
                    }
                }
            }
        } while (uncovered);
    }

    checkWin();

    //printDebug();
}

void Game::startGame(Field *clickedField)
{
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

        if (minefield[y][x] != mineMarker && x != clickedField->x && y != clickedField->y) {
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

void Game::maskAll()
{
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            minefieldMask[y][x] = 1;
        }
    }
}

void Game::uncoverAll()
{
    // Uncover all
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            minefieldMask[y][x] = 0;
        }
    }
}

void Game::uncoverNumbersAround(int x, int y)
{
    if (y > 0 && x > 0 && minefield[y-1][x-1] > 0) {
	    minefieldMask[y-1][x-1] = 0;
	}

	if (y > 0 && minefield[y-1][x] > 0) {
	    minefieldMask[y-1][x] = 0;
	}

	if (y > 0 && x < columns - 1 && minefield[y-1][x+1] > 0) {
	    minefieldMask[y-1][x+1] = 0;
	}

	if (x > 0 && minefield[y][x-1] > 0) {
	    minefieldMask[y][x-1] = 0;
	}

	if (x < columns - 1 && minefield[y][x+1] > 0) {
	    minefieldMask[y][x+1] = 0;
	}

	if (y < rows - 1 && x > 0 && minefield[y+1][x-1] > 0) {
	    minefieldMask[y+1][x-1] = 0;
	}

	if (y < rows - 1 && minefield[y+1][x] > 0) {
	    minefieldMask[y+1][x] = 0;
	}

	if (y < rows - 1 && x < columns - 1 && minefield[y+1][x+1] > 0) {
	    minefieldMask[y+1][x+1] = 0;
	}
}

void Game::checkWin()
{
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (minefieldMask[y][x] == 1 && minefield[y][x] != mineMarker) {
                return;
            }
        }
    }

    gameOver = true;
    won = true;
    gameStarted = false;
    uncoverAll();
}

void Game::printDebug()
{
    printf("MINEFIELD:\n");
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
