#include "Board.h"

Board::Board(
    SDL_Renderer *_renderer,
    TextureLoader *_textureLoader,
    int _offsetX,
    int _offsetY,
    int _rows,
    int _columns,
    IsoConvert *_isoConvert
) {
    renderer = _renderer;
    textureLoader = _textureLoader;
    offsetX = _offsetX;
    offsetY = _offsetY;
    rows = _rows;
    columns = _columns;
    isoConvert = _isoConvert;

    groundTex = textureLoader->load("resources/images/ground.png");
    groundTexHighlighted = textureLoader->load("resources/images/ground.png");
    deepGroundTex = textureLoader->load("resources/images/deep_ground.png");
    mineTex = textureLoader->load("resources/images/mine.png");
    boomTex = textureLoader->load("resources/images/mine.png");
    oneTex = textureLoader->load("resources/images/1.png");
    twoTex = textureLoader->load("resources/images/2.png");
    threeTex = textureLoader->load("resources/images/3.png");
    fourTex = textureLoader->load("resources/images/4.png");
    fiveTex = textureLoader->load("resources/images/5.png");
    sixTex = textureLoader->load("resources/images/6.png");
    sevenTex = textureLoader->load("resources/images/7.png");
    eightTex = textureLoader->load("resources/images/8.png");

    SDL_SetTextureColorMod(groundTexHighlighted, 255, 200, 50);
    SDL_SetTextureColorMod(boomTex, 255, 0, 0);
}

Board::~Board()
{
    //dtor
}

void Board::draw(int minefield[8][8], int minefieldMask[8][8])
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);

    // ground
    tileRect.w = mapTileWidth;
    tileRect.h = mapTileHeight;

    // Draw deep ground
    for (int y = 0; y < columns; y++) {
        for (int x = 0; x < rows; x++) {
            Point p = isoConvert->twoDToIso(mapTileScreenWidth * x, mapTileScreenHeight * y);
            tileRect.x = p.x + offsetX;
            tileRect.y = p.y + offsetY + deepGroundOffsetY;

            SDL_RenderCopy(renderer, deepGroundTex, NULL, &tileRect);
        }
    }

    // Draw numbers and mines
    for (int y = 0; y < columns; y++) {
        for (int x = 0; x < rows; x++) {
            Point p = isoConvert->twoDToIso(mapTileScreenWidth * x, mapTileScreenHeight * y);
            tileRect.x = p.x + offsetX;
            tileRect.y = p.y + offsetY;

            if (minefieldMask[y][x] == 1) {
                if (highlight != nullptr && highlight->x == x && highlight->y == y) {
                    SDL_RenderCopy(renderer, groundTexHighlighted, NULL, &tileRect);
                } else {
                    SDL_RenderCopy(renderer, groundTex, NULL, &tileRect);
                }
                continue;
            }

            switch (minefield[y][x]) {
                case -1:
                    SDL_RenderCopy(renderer, mineTex, NULL, &tileRect);
                    break;
                case -2:
                    SDL_RenderCopy(renderer, boomTex, NULL, &tileRect);
                    break;
                case 1:
                    SDL_RenderCopy(renderer, oneTex, NULL, &tileRect);
                    break;
                case 2:
                    SDL_RenderCopy(renderer, twoTex, NULL, &tileRect);
                    break;
                case 3:
                    SDL_RenderCopy(renderer, threeTex, NULL, &tileRect);
                    break;
                case 4:
                    SDL_RenderCopy(renderer, fourTex, NULL, &tileRect);
                    break;
                case 5:
                    SDL_RenderCopy(renderer, fiveTex, NULL, &tileRect);
                    break;
                case 6:
                    SDL_RenderCopy(renderer, sixTex, NULL, &tileRect);
                    break;
                case 7:
                    SDL_RenderCopy(renderer, sevenTex, NULL, &tileRect);
                    break;
                case 8:
                    SDL_RenderCopy(renderer, eightTex, NULL, &tileRect);
                    break;
            }
        }
    }
}

int Board::getMapTileScreenWidth()
{
    return mapTileScreenWidth;
}

int Board::getMapTileScreenHeight()
{
    return mapTileScreenHeight;
}
