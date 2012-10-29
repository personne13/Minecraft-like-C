#include "constantes.h"
#include "input.h"
#include "jeu.h"
#include "editeur.h"
#include "map.h"

Input event;
SDL_Surface *ecran = NULL;
int FOV = 70;

int main(int argc, char *argv[])
{
    GLenum initOK;
    /*SDL_Surface *heightMap = NULL;

    creerHeightMap(512, 512, TAILLECHUNK_Y, &heightMap);
    if(heightMap == NULL)
    {
        printf("erreur\n");
        exit(0);
    }
    SDL_SaveBMP(heightMap, "map/testMap/heightMap.bmp");

    SDL_FreeSurface(ecran);
    ecran = NULL;

    SDL_Quit();*/

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(FENETRE_LARG, FENETRE_HAUT, 32, SDL_OPENGL);
    SDL_WM_SetCaption("Minecraft-Like", NULL);

    if(ecran == NULL)
        printf("Erreur lors de la création de la fenêtre\n");


    initOK = glewInit();

    if(initOK != GLEW_OK)
    {
        printf("impossible d'initialiser GLEW : %s\n", glewGetErrorString(initOK));
    }

    SDL_EnableUNICODE(1);

    jouer();

    SDL_EnableUNICODE(0);

    SDL_Quit();

    return 0;
}
