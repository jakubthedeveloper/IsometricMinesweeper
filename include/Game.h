#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Board.h"
#include "Point.h"
#include "Field.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void mainLoop();
        static const int mineMarker = -1;
        static const int boomMarker = -2;

    protected:

    private:
        bool isRunning;
        bool gameStarted = false;
        bool gameOver = false;
        bool won = false;
        void handleEvents();
        void update();
        void render();
        void maskAll();
        void clickField(Field *point);
        Uint32 frameStart;
        int frameTime;
        const int frameDelay = 1000 / 60; // 60 FPS

        SDL_Window *window;
        SDL_Renderer *renderer;

        int columns = 8;
        int rows = 8;
        int numberOfMines = 10;
        int minefield[8][8];
        int minefieldMask[8][8];
        int windowWidth = 840;
        int windowHeight = 600;
        int windowFlags = 0;

        int offsetX = 370;
        int offsetY = 40;

        Board *board;
        void startGame(Field *clickedField);
        void printDebug();
        Point *mousePoint;
        Field *currentField;
        void convertScreenToIso(Point *point, Field *currentField);
        void uncoverNumbersAround(int x, int y);
        void checkWin();
        void uncoverAll();

        SDL_Texture* youWonTex;
        SDL_Texture* youLooseTex;
        SDL_Rect infoImgRect;
};

#endif // GAME_H
