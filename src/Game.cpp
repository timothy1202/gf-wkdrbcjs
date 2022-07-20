#include "Game.h"
#include "main.h"


SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/rider.bmp");

m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

SDL_FreeSurface(pTempSurface);