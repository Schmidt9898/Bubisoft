#include "Bubisoft_Net.hpp"

BUBISOFT_NET::BUBISOFT_NET()
{
    SDL_Init(SDL_INIT_EVERYTHING);///ha haszn�lsz sdl-t akkor ezt a sort szedd ki.
    SDLNet_Init();
}
BUBISOFT_NET __1;

