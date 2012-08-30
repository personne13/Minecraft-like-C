#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "input.h"

void updateEvents(Input* in)
{
    static SDL_Event event;
    int i;

    in->souris[SDL_BUTTON_WHEELUP] = 0;
    in->souris[SDL_BUTTON_WHEELDOWN] = 0;

    in->xrel = 0;
    in->yrel = 0;

    for(i = 0; i < SDLK_LAST; i++)
    {
        in->toucheUni[i] = 0;
    }

    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_KEYDOWN:
            in->touche[event.key.keysym.sym] = 1;
            in->toucheUni[event.key.keysym.unicode] = 1;
            break;
        case SDL_KEYUP:
            in->touche[event.key.keysym.sym] = 0;
            in->toucheUni[event.key.keysym.unicode] = 0;
            break;
        case SDL_MOUSEMOTION:
            in->posX = event.motion.x;
            in->posY = event.motion.y;
            in->xrel = event.motion.xrel;
            in->yrel = event.motion.yrel;
            break;
        case SDL_MOUSEBUTTONDOWN:
            in->souris[event.button.button] = 1;
            break;
        case SDL_MOUSEBUTTONUP:
            in->souris[event.button.button]=0;
            break;
        case SDL_QUIT:
            in->quitter = 1;
            break;
        default:
            break;
    }

    if(event.type == SDL_MOUSEMOTION)
    {
        event.motion.xrel = 0;
        event.motion.yrel = 0;
    }

    if(event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT)
    {
        event.button.button = 0;
    }

    if(event.key.keysym.sym < SDLK_LAST && event.key.keysym.sym > 0)
    {
        event.key.keysym.sym = SDLK_LAST;
    }

    event.key.keysym.unicode = SDLK_LAST;
}

void initialiserInput(Input *in)
{
    int i;

    in->quitter = 0;
    in->posX = 0;
    in->posY = 0;
    in->xrel = 0;
    in->yrel = 0;

    for(i = 0; i < 8; i++)
        in->souris[i] = 0;

    for(i = 0; i < SDLK_LAST; i++)
    {
        in->touche[i] = 0;
        in->toucheUni[i] = 0;
    }
}
