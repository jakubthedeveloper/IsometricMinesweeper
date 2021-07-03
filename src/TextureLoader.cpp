#include "TextureLoader.h"

TextureLoader::TextureLoader(SDL_Renderer *_renderer)
{
    renderer = _renderer;
}

TextureLoader::~TextureLoader()
{
    //dtor
}

SDL_Texture *TextureLoader::load(char *imagePath)
{
    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        printf("Failed to load image %s.", imagePath);
        exit(1);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}
