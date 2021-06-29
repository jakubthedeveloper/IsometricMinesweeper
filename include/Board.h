#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Point.h>
#include "IsoConvert.h"

class Board
{
    public:
        Board(SDL_Renderer *renderer, int offsetX, int offsetY, int rows, int columns);
        virtual ~Board();
        void draw();

        int getMapTileScreenWidth();
        int getMapTileScreenHeight();

    protected:

    private:
        SDL_Renderer *renderer;
        int offsetX;
        int offsetY;
        SDL_Texture* groundTex;
        int columns;
        int rows;

        int mapTileWidth = 100;
        int mapTileHeight = 65;
        int mapTileScreenWidth = 40;
        int mapTileScreenHeight = 40;

        SDL_Rect tileRect;
};

#endif // BOARD_H
