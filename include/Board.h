#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Point.h>
#include "IsoConvert.h"

class Board
{
    public:
        Board(SDL_Renderer *renderer);
        virtual ~Board();
        void draw();

    protected:

    private:
        SDL_Renderer *renderer;
        int offsetX = 350;
        int offsetY = 60;
        SDL_Texture* groundTex;
        int cols = 8;
        int rows = 8;

        int mapTileWidth = 100;
        int mapTileHeight = 65;
        int mapTileScreenWidth = 40;
        int mapTileScreenHeight = 40;

        SDL_Rect tileRect;
};

#endif // BOARD_H
