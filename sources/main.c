#include "constantes.h"
#include "input.h"
#include "jeu.h"
#include "editeur.h"

Input event;
SDL_Surface *ecran = NULL;

int main(int argc, char *argv[])
{
    GLenum initOK;
    //Démarrage de l'application pour le mode d'édition.
    /*SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(FENETRE_LARG, FENETRE_HAUT, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Minecraft-Like", NULL);

    if(ecran == NULL)
        printf("Erreur lors de la création de la fenêtre\n");

    editerMap();

    SDL_FreeSurface(ecran);
    ecran = NULL;

    SDL_Quit();*/

    //Démarrage de l'application pour le mode d'exploration.
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(FENETRE_LARG, FENETRE_HAUT, 32, SDL_OPENGL);
    SDL_WM_SetCaption("Minecraft-Like", NULL);

    initOK = glewInit();

    if(initOK != GLEW_OK)
    {
        printf("impossible d'initialiser GLEW : %s\n", glewGetErrorString(initOK));
    }

    /*PFNGLGENBUFFERSARBPROC glGenBuffers;

    const char * glVersion = (const char *) glGetString(GL_EXTENSIONS);

    printf("Version : %s\n", glVersion);

    glGenBuffers = SDL_GL_GetProcAddress("glGenBuffersARB");*/

    SDL_EnableUNICODE(1);

    if(ecran == NULL)
        printf("Erreur lors de la création de la fenêtre\n");

    jouer();

    SDL_EnableUNICODE(0);

    SDL_Quit();

    return 0;
}
