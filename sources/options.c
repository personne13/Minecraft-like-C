#include "constantes.h"
#include "options.h"

void sauvegarderCommandes(Commandes com, char *chemin)
{
    FILE *fichier = NULL;

    fichier = fopen(chemin, "w+");

    if(fichier != NULL)
    {
        fprintf(fichier, "avancer = %d\n", com.avancer);
        fprintf(fichier, "reculer = %d\n", com.reculer);
        fprintf(fichier, "gauche = %d\n", com.gauche);
        fprintf(fichier, "droite = %d\n", com.droite);
        fprintf(fichier, "attaquer = %d\n", com.attaquer);
        fprintf(fichier, "utiliser = %d\n", com.utiliser);
        fprintf(fichier, "sneak = %d\n", com.sneak);
        fprintf(fichier, "sauter = %d\n", com.sauter);
        fprintf(fichier, "inventaire = %d\n", com.inv);
        fprintf(fichier, "drop = %d\n", com.drop);
        fprintf(fichier, "chat = %d\n", com.chat);
        fprintf(fichier, "liste joueurs = %d\n", com.listeJoueurs);
        fprintf(fichier, "prendre bloc = %d\n", com.prendreBloc);
    }
    else
    {
        printf("Impossible de créer le fichier : %s\n", chemin);
        exit(EXIT_FAILURE);
    }

    fclose(fichier);
}

void chargerCommandes(Commandes *com, char *chemin)
{
    FILE *fichier = NULL;
    fichier = fopen(chemin, "r");

    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier des commandes (%s)\n", chemin);
        exit(EXIT_FAILURE);
    }

    //Touches par défaut
    com->avancer = SDLK_w;
    com->reculer = SDLK_s;
    com->droite = SDLK_d;
    com->gauche = SDLK_a;
    com->inv = SDLK_e;
    com->attaquer = SDL_BUTTON_LEFT;
    com->utiliser = SDL_BUTTON_RIGHT;
    com->sneak = SDLK_LSHIFT;
    com->sauter = SDLK_SPACE;
    com->drop = SDLK_a;
    com->chat = SDLK_t;
    com->listeJoueurs = SDLK_TAB;
    com->prendreBloc = SDL_BUTTON_MIDDLE;

    if(fichier != NULL)
    {
        fscanf(fichier, "avancer = %d\n", &com->avancer);
        fscanf(fichier, "reculer = %d\n", &com->reculer);
        fscanf(fichier, "gauche = %d\n", &com->gauche);
        fscanf(fichier, "droite = %d\n", &com->droite);
        fscanf(fichier, "attaquer = %d\n", &com->attaquer);
        fscanf(fichier, "utiliser = %d\n", &com->utiliser);
        fscanf(fichier, "sneak = %d\n", &com->sneak);
        fscanf(fichier, "sauter = %d\n", &com->sauter);
        fscanf(fichier, "inventaire = %d\n", &com->inv);
        fscanf(fichier, "drop = %d\n", &com->drop);
        fscanf(fichier, "chat = %d\n", &com->chat);
        fscanf(fichier, "liste joueurs = %d\n", &com->listeJoueurs);
        fscanf(fichier, "prendre bloc = %d\n", &com->prendreBloc);
    }
    else
    {
        printf("Impossible de charger le fichier %s\n", chemin);
    }

    fclose(fichier);
}
