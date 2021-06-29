#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Board.h"


class Game
{
    public:
        Game();
        virtual ~Game();
        void mainLoop();

    protected:

    private:
        bool isRunning;
        void handleEvents();
        void update();
        void render();
        void click(int screenX, int screenY);
        Uint32 frameStart;
        int frameTime;
        const int frameDelay = 1000 / 60; // 60 FPS

        SDL_Window *window;
        SDL_Renderer *renderer;

        int windowWidth = 800;
        int windowHeight = 600;
        int windowFlags = 0;

        int offsetX = 350;
        int offsetY = 60;

        Board *board;
};

#endif // GAME_H
