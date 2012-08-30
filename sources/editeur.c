#include "constantes.h"
#include "editeur.h"
#include "input.h"
#include "map.h"

extern Input event;
extern SDL_Surface *ecran;

void editerMap()
{
    int continuer = 1;
    int yActuel = 0, tpsActuel = 0, tpsPrecedent = 0;
    Chunk terrain;

    initialiserInput(&event);

    while(continuer)
    {
        updateEvents(&event);

        if(event.quitter == 1)
            exit(EXIT_SUCCESS);
        if(event.touche[SDLK_ESCAPE] == 1)
            continuer = 0;

        if(event.souris[SDL_BUTTON_LEFT] == 1 || event.souris[SDL_BUTTON_RIGHT] == 1)
            remplirTerrain(&terrain, yActuel);
        if(event.touche[SDLK_s] == 1)
        {
            sauvegarderMapF("map/test.map", terrain);
            printf("Sauvegardé\n");
            event.touche[SDLK_s] = 0;
        }

        if(event.touche[SDLK_LALT] == 1)
        {
            if(yActuel > 0)
                yActuel--;

            printf("%d\n", yActuel);

            event.touche[SDLK_LALT] = 0;
        }

        if(event.touche[SDLK_SPACE] == 1)
        {
            if(yActuel < 127)
                yActuel++;

            printf("%d\n", yActuel);

            event.touche[SDLK_SPACE] = 0;
        }

        tpsActuel = SDL_GetTicks();

        if(tpsActuel - tpsPrecedent > 50)
        {
            affichageEditeur(terrain, yActuel);
            tpsPrecedent = tpsActuel;
        }
        else
            SDL_Delay(50 - (tpsActuel - tpsPrecedent));
    }
}

void affichageEditeur(Chunk terrain, int yActuel)
{
    int w, h;
    int i, x, z;
    SDL_Rect traitHorizontal[17], traitVertical[17];
    SDL_Rect carreau;

    w = FENETRE_LARG / 16;
    h = FENETRE_HAUT / 16;

    carreau.w = w;
    carreau.h = h;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    for(x = 0; x < 16; x++)
    {
        for(z = 0; z < 16; z++)
        {
            if(terrain.entite[x][yActuel][z] == 1)
            {
                carreau.x = x * w;
                carreau.y = z * h;

                SDL_FillRect(ecran, &carreau, SDL_MapRGB(ecran->format, 0, 0, 0));
            }
        }
    }

    for(i = 0; i < 16 + 1; i++)
    {
        traitHorizontal[i].h = 1;
        traitHorizontal[i].w = FENETRE_LARG;
        traitHorizontal[i].x = 0;
        traitHorizontal[i].y = i * h;
        traitVertical[i].h = FENETRE_HAUT;
        traitVertical[i].w = 1;
        traitVertical[i].x = i * w;
        traitVertical[i].y = 0;
    }

    for(i = 0; i < 16 + 1; i++)
    {
        SDL_FillRect(ecran, &traitHorizontal[i], SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_FillRect(ecran, &traitVertical[i], SDL_MapRGB(ecran->format, 0, 0, 0));
    }
    SDL_Flip(ecran);
}

void remplirTerrain(Chunk *terrain, int yActuel)
{
    int w, h;
    int x, z;

    w = FENETRE_LARG / 16;
    h = FENETRE_HAUT / 16;

    x = event.posX / w;
    z = event.posY / h;

    if(event.souris[SDL_BUTTON_LEFT] == 1)
        terrain->entite[x][yActuel][z] = 1;
    if(event.souris[SDL_BUTTON_RIGHT] == 1)
        terrain->entite[x][yActuel][z] = 0;
}
