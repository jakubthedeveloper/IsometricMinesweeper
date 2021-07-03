#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureLoader
{
    public:
        TextureLoader(SDL_Renderer *_renderer);
        virtual ~TextureLoader();
        SDL_Texture *load(char *imagePath);

    protected:

    private:
        SDL_Renderer *renderer;
};

#endif // TEXTURELOADER_H
