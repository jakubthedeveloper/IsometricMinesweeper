#include "Gui.h"

Gui::Gui(SDL_Renderer *_renderer, TextureLoader *_textureLoader)
{
    renderer = _renderer;
    textureLoader = _textureLoader;

    youWonTex = textureLoader->load("resources/images/you-won.png");
    youLooseTex = textureLoader->load("resources/images/you-lose.png");
}

Gui::~Gui()
{
    //dtor
}

void Gui::drawYouWon()
{
    SDL_RenderCopy(renderer, youWonTex, NULL, &infoImgRect);
}

void Gui::drawYouLoose()
{
    SDL_RenderCopy(renderer, youLooseTex, NULL, &infoImgRect);
}
