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
        Uint32 frameStart;
        int frameTime;
        const int frameDelay = 1000 / 60; // 60 FPS

        SDL_Window *window;
        SDL_Renderer *renderer;

        int windowWidth = 800;
        int windowHeight = 600;
        int windowFlags = 0;

        Board *board;
};

#endif // GAME_H
