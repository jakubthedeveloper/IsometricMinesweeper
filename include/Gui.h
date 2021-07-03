#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureLoader.h"

class Gui
{
    public:
        Gui(SDL_Renderer *renderer, TextureLoader *textureLoader);
        virtual ~Gui();
        void drawYouWon();
        void drawYouLoose();

    protected:

    private:
        TextureLoader *textureLoader;
        SDL_Renderer *renderer;
        SDL_Texture *youWonTex;
        SDL_Texture *youLooseTex;
        SDL_Rect infoImgRect = {
            110, // x
            470, // y
            600, // w
            143  // h
        };
};

#endif // GUI_H
