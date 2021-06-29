#include "Board.h"

Board::Board(SDL_Renderer *_renderer, int _offsetX, int _offsetY, int _rows, int _columns)
{
    renderer = _renderer;
    offsetX = _offsetX;
    offsetY = _offsetY;
    rows = _rows;
    columns = _columns;

    SDL_Surface* groundSurface = IMG_Load("resources/images/ground.png");
    SDL_Surface* deepGroundSurface = IMG_Load("resources/images/deep_ground.png");
    SDL_Surface* mineSurface = IMG_Load("resources/images/mine.png");
    SDL_Surface* oneSurface = IMG_Load("resources/images/1.png");
    SDL_Surface* twoSurface = IMG_Load("resources/images/2.png");
    SDL_Surface* threeSurface = IMG_Load("resources/images/3.png");
    SDL_Surface* fourSurface = IMG_Load("resources/images/4.png");
    SDL_Surface* fiveSurface = IMG_Load("resources/images/5.png");
    SDL_Surface* sixSurface = IMG_Load("resources/images/6.png");
    SDL_Surface* sevenSurface = IMG_Load("resources/images/7.png");
    SDL_Surface* eightSurface = IMG_Load("resources/images/8.png");

    if (!groundSurface) { printf("Failed to load ground image."); exit(1); }
    if (!deepGroundSurface) { printf("Failed to load deep ground image."); exit(1); }
    if (!mineSurface) { printf("Failed to load ground image."); exit(1); }
    if (!oneSurface) { printf("Failed to load one image."); exit(1); }
    if (!twoSurface) { printf("Failed to load two image."); exit(1); }
    if (!threeSurface) { printf("Failed to load three image."); exit(1); }
    if (!fourSurface) { printf("Failed to load four image."); exit(1); }
    if (!fiveSurface) { printf("Failed to load five image."); exit(1); }
    if (!sixSurface) { printf("Failed to load six image."); exit(1); }
    if (!sevenSurface) { printf("Failed to load seven image."); exit(1); }
    if (!eightSurface) { printf("Failed to load eight image."); exit(1); }

    groundTex = SDL_CreateTextureFromSurface(renderer, groundSurface);
    deepGroundTex = SDL_CreateTextureFromSurface(renderer, deepGroundSurface);
    mineTex = SDL_CreateTextureFromSurface(renderer, mineSurface);
    oneTex = SDL_CreateTextureFromSurface(renderer, oneSurface);
    twoTex = SDL_CreateTextureFromSurface(renderer, twoSurface);
    threeTex = SDL_CreateTextureFromSurface(renderer, threeSurface);
    fourTex = SDL_CreateTextureFromSurface(renderer, fourSurface);
    fiveTex = SDL_CreateTextureFromSurface(renderer, fiveSurface);
    sixTex = SDL_CreateTextureFromSurface(renderer, sixSurface);
    sevenTex = SDL_CreateTextureFromSurface(renderer, sevenSurface);
    eightTex = SDL_CreateTextureFromSurface(renderer, eightSurface);

    SDL_FreeSurface(groundSurface);
    SDL_FreeSurface(deepGroundSurface);
    SDL_FreeSurface(mineSurface);
    SDL_FreeSurface(oneSurface);
    SDL_FreeSurface(twoSurface);
    SDL_FreeSurface(threeSurface);
    SDL_FreeSurface(fourSurface);
    SDL_FreeSurface(fiveSurface);
    SDL_FreeSurface(sixSurface);
    SDL_FreeSurface(sevenSurface);
    SDL_FreeSurface(eightSurface);
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
            Point p = IsoConvert::twoDToIso(mapTileScreenWidth * x, mapTileScreenHeight * y);
            tileRect.x = p.x + offsetX;
            tileRect.y = p.y + offsetY + deepGroundOffsetY;

            SDL_RenderCopy(renderer, deepGroundTex, NULL, &tileRect);
        }
    }

    // Draw numbers and mines
    for (int y = 0; y < columns; y++) {
        for (int x = 0; x < rows; x++) {
            Point p = IsoConvert::twoDToIso(mapTileScreenWidth * x, mapTileScreenHeight * y);
            tileRect.x = p.x + offsetX;
            tileRect.y = p.y + offsetY;

            if (minefieldMask[y][x] == 1) {
                SDL_RenderCopy(renderer, groundTex, NULL, &tileRect);
                continue;
            }

            switch (minefield[y][x]) {
                case -1:
                    SDL_RenderCopy(renderer, mineTex, NULL, &tileRect);
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
