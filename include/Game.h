#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "TextureLoader.h"
#include "Gui.h"
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
        TextureLoader *textureLoader;
        Board *board;
        Gui *gui;
        Point *mousePoint;
        Field *currentField;
        IsoConvert *isoConvert;
        SDL_Window *window;
        SDL_Renderer *renderer;

        bool isRunning;
        bool gameStarted = false;
        bool gameOver = false;
        bool won = false;
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
        Uint32 frameStart;
        int frameTime;
        const int frameDelay = 1000 / 60; // 60 FPS

        void handleEvents();
        void update();
        void render();
        void maskAll();
        void clickField(Field *point);
        void startGame(Field *clickedField);
        void printDebug();
        void uncoverNumbersAround(int x, int y);
        void checkWin();
        void uncoverAll();
};

#endif // GAME_H
