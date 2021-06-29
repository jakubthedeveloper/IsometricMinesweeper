#include "Board.h"

Board::Board(SDL_Renderer *_renderer)
{
    renderer = _renderer;

    SDL_Surface* groundSurface = IMG_Load("resources/images/ground.png");

    if (!groundSurface) {
        printf("Failed to load ground image.");
        exit(1);
    }

    groundTex = SDL_CreateTextureFromSurface(renderer, groundSurface);
    SDL_FreeSurface(groundSurface);
}

Board::~Board()
{
    //dtor
}

void Board::draw()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);

    // ground
    tileRect.w = mapTileWidth;
    tileRect.h = mapTileHeight;

    for (int y = 0; y < cols; y++) {
        for (int x = 0; x < rows; x++) {
            Point p = IsoConvert::twoDToIso(mapTileScreenWidth * x, mapTileScreenHeight * y);
            tileRect.x = p.x + offsetX;
            tileRect.y = p.y + offsetY;

            SDL_RenderCopy(renderer, groundTex, NULL, &tileRect);
        }
    }
}
