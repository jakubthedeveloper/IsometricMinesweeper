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
        void draw(int minefield[8][8], int minefieldMask[8][8]);

        int getMapTileScreenWidth();
        int getMapTileScreenHeight();

    protected:

    private:
        SDL_Renderer *renderer;
        int offsetX;
        int offsetY;
        SDL_Texture* groundTex;
        SDL_Texture* deepGroundTex;
        SDL_Texture* mineTex;
        SDL_Texture* oneTex;
        SDL_Texture* twoTex;
        SDL_Texture* threeTex;
        SDL_Texture* fourTex;
        SDL_Texture* fiveTex;
        SDL_Texture* sixTex;
        SDL_Texture* sevenTex;
        SDL_Texture* eightTex;
        int columns;
        int rows;

        int mapTileWidth = 100;
        int mapTileHeight = 65;
        int mapTileScreenWidth = 40;
        int mapTileScreenHeight = 40;
        int deepGroundOffsetY = 2;

        SDL_Rect tileRect;
};

#endif // BOARD_H
