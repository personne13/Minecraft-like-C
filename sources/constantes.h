#ifndef CONSTANTES
#define CONSTANTES

    #include <SDL.h>
    #include <SDL/SDL_image.h>
    #include <GL/glew.h>

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <time.h>
    #include <string.h>

    #define FENETRE_LARG 800
    #define FENETRE_HAUT 600
    #define TAILLECHUNK_X 16
    #define TAILLECHUNK_Y 256
    #define TAILLECHUNK_Z 16
    #define NOMBRE_ENTITE 124
    #define NOMBRE_BLOCS 124
    #define NOMBRE_ITEMS 148
    #define CHUNK_MEM 3

    enum {BOUTON_TYPE_STANDARD, BOUTON_TYPE_VARIATION};

    ///Déclaration des structures

    typedef struct Point Point;
    struct Point
    {
        double x, y, z;
    };

    typedef struct Couleur Couleur;
    struct Couleur
    {
        float r, v, b;
    };

    typedef struct Face Face;
    struct Face
    {
        Point bas1, bas2, haut1, haut2; //Les quatres points de la face
        int IdTexture;
        Couleur couleur;
    };

    typedef struct Chunk Chunk;
    struct Chunk
    {
        int entite[TAILLECHUNK_X][TAILLECHUNK_Y][TAILLECHUNK_Z];//Tableau pour stocker les ID des blocs
        int posX, posZ;
        int hauteurMax;
        int modifie;
    };

    typedef struct Map Map;
    struct Map
    {
        Chunk *chunk;
    };


    typedef struct Pave Pave;//Structure bloc
    struct Pave
    {
        Face face[6];
        int ID;
        GLuint IDVBO;
    };

    typedef struct Item Item;
    struct Item
    {
        int ID;
        int IDTex;
    };

    typedef struct Inventaire Inventaire;
    struct Inventaire
    {
        int IDEntite[36];
        int quantite[36];
    };

    typedef struct Texture Texture;//Le système de coordonnées est le même que la SDL
    struct Texture
    {
        GLuint IDtex;//Id de la texture à appliquer
        int posX, posY;//La position de la texture sur la fenêtre (point haut gauche)
        int posTexX, posTexY;//Le point de la texture (le fichier) à afficher
        int weight, height;//Largeur et hauteur
        int wMax, hMax;//Largeur et hauteur totale du fichier (ex : 512*512)
    };

    typedef struct Commandes Commandes;
    struct Commandes
    {
        int avancer, reculer, droite, gauche;
        int inv;
        int attaquer, utiliser;
        int sneak, sauter;
        int drop;
        int chat;
        int listeJoueurs;
        int prendreBloc;
    };

    typedef struct Texte Texte;
    struct Texte
    {
        char *chaine;
        int nbCara;
        int ombre;
    };

    typedef struct Bouton Bouton;
    struct Bouton
    {
        GLuint IDtex;
        int posX, posY;
        int weight, height;
        int posTex1DebX, posTex1DebY;//point haut-gauche de la texture 1 (standard, non sélectionné)
        int posTex1FinX, posTex1FinY;//point bas-droite de la texture 1
        int posTex2DebX, posTex2DebY;//point haut-gauche de la texture 2 (standard, sélectionné)
        int posTex2FinX, posTex2FinY;//point bas-droite de la texture 2
        int posTex3DebX, posTex3DebY;//point haut-gauche de la texture 3 (bouton variation)
        int posTex3FinX, posTex3FinY;//point bas-droite de la texture 3
        int wMax, hMax;
        int selectionne;
        Texte texte;
        int type;
    };

    typedef struct Mob Mob;
    struct Mob
    {
        Pave *membre;
        int nombreMembres;
        int largeur, hauteur, profondeur;
        Texture *tex;
    };

#endif
