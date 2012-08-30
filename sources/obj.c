#include "constantes.h"
#include "obj.h"
#include "Input.h"
#include "jeu.h"

void attribuerCube(Pave *cube, double dimension)
{
    cube->face[0].bas1.x = dimension;
    cube->face[0].bas1.y = (double)0.0;
    cube->face[0].bas1.z = (double)0.0;

    cube->face[0].bas2.x = (double)0.0;
    cube->face[0].bas2.y = (double)0.0;
    cube->face[0].bas2.z = (double)0.0;

    cube->face[0].haut1.x = dimension;
    cube->face[0].haut1.y = dimension;
    cube->face[0].haut1.z = (double)0.0;

    cube->face[0].haut2.x = (double)0.0;
    cube->face[0].haut2.y = dimension;
    cube->face[0].haut2.z = (double)0.0;


    cube->face[1].bas1.x = (double)0.0;
    cube->face[1].bas1.y = (double)0.0;
    cube->face[1].bas1.z = (double)0.0;

    cube->face[1].bas2.x = (double)0.0;
    cube->face[1].bas2.y = (double)0.0;
    cube->face[1].bas2.z = dimension;

    cube->face[1].haut1.x = (double)0.0;
    cube->face[1].haut1.y = dimension;
    cube->face[1].haut1.z = (double)0.0;

    cube->face[1].haut2.x = (double)0.0;
    cube->face[1].haut2.y = dimension;
    cube->face[1].haut2.z = dimension;


    cube->face[2].bas1.x = (double)0.0;
    cube->face[2].bas1.y = (double)0.0;
    cube->face[2].bas1.z = dimension;

    cube->face[2].bas2.x = dimension;
    cube->face[2].bas2.y = (double)0.0;
    cube->face[2].bas2.z = dimension;

    cube->face[2].haut1.x = (double)0.0;
    cube->face[2].haut1.y = dimension;
    cube->face[2].haut1.z = dimension;

    cube->face[2].haut2.x = dimension;
    cube->face[2].haut2.y = dimension;
    cube->face[2].haut2.z = dimension;


    cube->face[3].bas1.x = dimension;
    cube->face[3].bas1.y = (double)0.0;
    cube->face[3].bas1.z = dimension;

    cube->face[3].bas2.x = dimension;
    cube->face[3].bas2.y = (double)0.0;
    cube->face[3].bas2.z = (double)0.0;

    cube->face[3].haut1.x = dimension;
    cube->face[3].haut1.y = dimension;
    cube->face[3].haut1.z = dimension;

    cube->face[3].haut2.x = dimension;
    cube->face[3].haut2.y = dimension;
    cube->face[3].haut2.z = (double)0.0;


    cube->face[4].bas1.x = (double)0.0;
    cube->face[4].bas1.y = (double)0.0;
    cube->face[4].bas1.z = (double)0.0;

    cube->face[4].bas2.x = (double)0.0;
    cube->face[4].bas2.y = (double)0.0;
    cube->face[4].bas2.z = dimension;

    cube->face[4].haut1.x = dimension;
    cube->face[4].haut1.y = (double)0.0;
    cube->face[4].haut1.z = (double)0.0;

    cube->face[4].haut2.x = dimension;
    cube->face[4].haut2.y = (double)0.0;
    cube->face[4].haut2.z = dimension;


    cube->face[5].bas1.x = (double)0.0;
    cube->face[5].bas1.y = dimension;
    cube->face[5].bas1.z = (double)0.0;

    cube->face[5].bas2.x = (double)0.0;
    cube->face[5].bas2.y = dimension;
    cube->face[5].bas2.z = dimension;

    cube->face[5].haut1.x = dimension;
    cube->face[5].haut1.y = dimension;
    cube->face[5].haut1.z = (double)0.0;

    cube->face[5].haut2.x = dimension;
    cube->face[5].haut2.y = dimension;
    cube->face[5].haut2.z = dimension;
}

void attribuerPersonnage(Mob *personnage, GLuint tex)
{
    int i;

    personnage->nombreMembres = 6;
    personnage->membre = malloc(personnage->nombreMembres * sizeof(Pave));
    personnage->tex = malloc(personnage->nombreMembres * 6 * sizeof(Texture));

    for(i = 0; i < personnage->nombreMembres * 6; i++)
    {
        personnage->tex[i].IDtex = tex;
    }

    personnage->hauteur = 1.75;
    personnage->largeur = 1;
    personnage->profondeur = 0.5;

    //Jambe gauche

    personnage->membre[0].face[0].bas1.x = -0.125;
    personnage->membre[0].face[0].bas1.y = -0.65;
    personnage->membre[0].face[0].bas1.z = -0.125;

    personnage->membre[0].face[0].bas2.x = 0.125;
    personnage->membre[0].face[0].bas2.y = -0.65;
    personnage->membre[0].face[0].bas2.z = -0.125;

    personnage->membre[0].face[0].haut1.x = -0.125;
    personnage->membre[0].face[0].haut1.y = 0;
    personnage->membre[0].face[0].haut1.z = -0.125;

    personnage->membre[0].face[0].haut2.x = 0.125;
    personnage->membre[0].face[0].haut2.y = 0;
    personnage->membre[0].face[0].haut2.z = -0.125;

    personnage->tex[0].height = 12;
    personnage->tex[0].weight = 4;
    personnage->tex[0].posTexX = 4;
    personnage->tex[0].posTexY = 20;
    personnage->tex[0].hMax = 32;
    personnage->tex[0].wMax = 64;


    personnage->membre[0].face[1].bas1.x = -0.125;
    personnage->membre[0].face[1].bas1.y = -0.65;
    personnage->membre[0].face[1].bas1.z = -0.125;

    personnage->membre[0].face[1].bas2.x = -0.125;
    personnage->membre[0].face[1].bas2.y = -0.65;
    personnage->membre[0].face[1].bas2.z = 0.125;

    personnage->membre[0].face[1].haut1.x = -0.125;
    personnage->membre[0].face[1].haut1.y = 0;
    personnage->membre[0].face[1].haut1.z = -0.125;

    personnage->membre[0].face[1].haut2.x = -0.125;
    personnage->membre[0].face[1].haut2.y = 0;
    personnage->membre[0].face[1].haut2.z = 0.125;

    personnage->tex[1].height = 12;
    personnage->tex[1].weight = 4;
    personnage->tex[1].posTexX = 0;
    personnage->tex[1].posTexY = 20;
    personnage->tex[1].hMax = 32;
    personnage->tex[1].wMax = 64;


    personnage->membre[0].face[2].bas1.x = -0.125;
    personnage->membre[0].face[2].bas1.y = -0.65;
    personnage->membre[0].face[2].bas1.z = 0.125;

    personnage->membre[0].face[2].bas2.x = 0.125;
    personnage->membre[0].face[2].bas2.y = -0.65;
    personnage->membre[0].face[2].bas2.z = 0.125;

    personnage->membre[0].face[2].haut1.x = -0.125;
    personnage->membre[0].face[2].haut1.y = 0;
    personnage->membre[0].face[2].haut1.z = 0.125;

    personnage->membre[0].face[2].haut2.x = 0.125;
    personnage->membre[0].face[2].haut2.y = 0;
    personnage->membre[0].face[2].haut2.z = 0.125;

    personnage->tex[2].height = 12;
    personnage->tex[2].weight = 4;
    personnage->tex[2].posTexX = 12;
    personnage->tex[2].posTexY = 20;
    personnage->tex[2].hMax = 32;
    personnage->tex[2].wMax = 64;


    personnage->membre[0].face[3].bas1.x = 0.125;
    personnage->membre[0].face[3].bas1.y = -0.65;
    personnage->membre[0].face[3].bas1.z = 0.125;

    personnage->membre[0].face[3].bas2.x = 0.125;
    personnage->membre[0].face[3].bas2.y = -0.65;
    personnage->membre[0].face[3].bas2.z = -0.125;

    personnage->membre[0].face[3].haut1.x = 0.125;
    personnage->membre[0].face[3].haut1.y = 0;
    personnage->membre[0].face[3].haut1.z = 0.125;

    personnage->membre[0].face[3].haut2.x = 0.125;
    personnage->membre[0].face[3].haut2.y = 0;
    personnage->membre[0].face[3].haut2.z = -0.125;

    personnage->tex[3].height = 12;
    personnage->tex[3].weight = 4;
    personnage->tex[3].posTexX = 8;
    personnage->tex[3].posTexY = 20;
    personnage->tex[3].hMax = 32;
    personnage->tex[3].wMax = 64;


    personnage->membre[0].face[4].bas1.x = -0.125;
    personnage->membre[0].face[4].bas1.y = -0.65;
    personnage->membre[0].face[4].bas1.z = -0.125;

    personnage->membre[0].face[4].bas2.x = -0.125;
    personnage->membre[0].face[4].bas2.y = -0.65;
    personnage->membre[0].face[4].bas2.z = 0.125;

    personnage->membre[0].face[4].haut1.x = 0.125;
    personnage->membre[0].face[4].haut1.y = -0.65;
    personnage->membre[0].face[4].haut1.z = -0.125;

    personnage->membre[0].face[4].haut2.x = 0.125;
    personnage->membre[0].face[4].haut2.y = -0.65;
    personnage->membre[0].face[4].haut2.z = 0.125;

    personnage->tex[4].height = 4;
    personnage->tex[4].weight = 4;
    personnage->tex[4].posTexX = 8;
    personnage->tex[4].posTexY = 16;
    personnage->tex[4].hMax = 32;
    personnage->tex[4].wMax = 64;


    personnage->membre[0].face[5].bas1.x = -0.125;
    personnage->membre[0].face[5].bas1.y = 0;
    personnage->membre[0].face[5].bas1.z = -0.125;

    personnage->membre[0].face[5].bas2.x = -0.125;
    personnage->membre[0].face[5].bas2.y = 0;
    personnage->membre[0].face[5].bas2.z = 0.125;

    personnage->membre[0].face[5].haut1.x = 0.125;
    personnage->membre[0].face[5].haut1.y = 0;
    personnage->membre[0].face[5].haut1.z = -0.125;

    personnage->membre[0].face[5].haut2.x = 0.125;
    personnage->membre[0].face[5].haut2.y = 0;
    personnage->membre[0].face[5].haut2.z = 0.125;

    personnage->tex[5].height = 4;
    personnage->tex[5].weight = 4;
    personnage->tex[5].posTexX = 4;
    personnage->tex[5].posTexY = 16;
    personnage->tex[5].hMax = 32;
    personnage->tex[5].wMax = 64;

    //Jambe droite

    personnage->membre[1].face[0].bas1.x = -0.125;
    personnage->membre[1].face[0].bas1.y = -0.65;
    personnage->membre[1].face[0].bas1.z = -0.125;

    personnage->membre[1].face[0].bas2.x = 0.125;
    personnage->membre[1].face[0].bas2.y = -0.65;
    personnage->membre[1].face[0].bas2.z = -0.125;

    personnage->membre[1].face[0].haut1.x = -0.125;
    personnage->membre[1].face[0].haut1.y = 0;
    personnage->membre[1].face[0].haut1.z = -0.125;

    personnage->membre[1].face[0].haut2.x = 0.125;
    personnage->membre[1].face[0].haut2.y = 0;
    personnage->membre[1].face[0].haut2.z = -0.125;

    personnage->tex[6].height = 12;
    personnage->tex[6].weight = 4;
    personnage->tex[6].posTexX = 4;
    personnage->tex[6].posTexY = 20;
    personnage->tex[6].hMax = 32;
    personnage->tex[6].wMax = 64;


    personnage->membre[1].face[1].bas1.x = -0.125;
    personnage->membre[1].face[1].bas1.y = -0.65;
    personnage->membre[1].face[1].bas1.z = -0.125;

    personnage->membre[1].face[1].bas2.x = -0.125;
    personnage->membre[1].face[1].bas2.y = -0.65;
    personnage->membre[1].face[1].bas2.z = 0.125;

    personnage->membre[1].face[1].haut1.x = -0.125;
    personnage->membre[1].face[1].haut1.y = 0;
    personnage->membre[1].face[1].haut1.z = -0.125;

    personnage->membre[1].face[1].haut2.x = -0.125;
    personnage->membre[1].face[1].haut2.y = 0;
    personnage->membre[1].face[1].haut2.z = 0.125;

    personnage->tex[7].height = 12;
    personnage->tex[7].weight = 4;
    personnage->tex[7].posTexX = 8;
    personnage->tex[7].posTexY = 20;
    personnage->tex[7].hMax = 32;
    personnage->tex[7].wMax = 64;


    personnage->membre[1].face[2].bas1.x = -0.125;
    personnage->membre[1].face[2].bas1.y = -0.65;
    personnage->membre[1].face[2].bas1.z = 0.125;

    personnage->membre[1].face[2].bas2.x = 0.125;
    personnage->membre[1].face[2].bas2.y = -0.65;
    personnage->membre[1].face[2].bas2.z = 0.125;

    personnage->membre[1].face[2].haut1.x = -0.125;
    personnage->membre[1].face[2].haut1.y = 0;
    personnage->membre[1].face[2].haut1.z = 0.125;

    personnage->membre[1].face[2].haut2.x = 0.125;
    personnage->membre[1].face[2].haut2.y = 0;
    personnage->membre[1].face[2].haut2.z = 0.125;

    personnage->tex[8].height = 12;
    personnage->tex[8].weight = 4;
    personnage->tex[8].posTexX = 12;
    personnage->tex[8].posTexY = 20;
    personnage->tex[8].hMax = 32;
    personnage->tex[8].wMax = 64;


    personnage->membre[1].face[3].bas1.x = 0.125;
    personnage->membre[1].face[3].bas1.y = -0.65;
    personnage->membre[1].face[3].bas1.z = 0.125;

    personnage->membre[1].face[3].bas2.x = 0.125;
    personnage->membre[1].face[3].bas2.y = -0.65;
    personnage->membre[1].face[3].bas2.z = -0.125;

    personnage->membre[1].face[3].haut1.x = 0.125;
    personnage->membre[1].face[3].haut1.y = 0;
    personnage->membre[1].face[3].haut1.z = 0.125;

    personnage->membre[1].face[3].haut2.x = 0.125;
    personnage->membre[1].face[3].haut2.y = 0;
    personnage->membre[1].face[3].haut2.z = -0.125;

    personnage->tex[9].height = 12;
    personnage->tex[9].weight = 4;
    personnage->tex[9].posTexX = 0;
    personnage->tex[9].posTexY = 20;
    personnage->tex[9].hMax = 32;
    personnage->tex[9].wMax = 64;


    personnage->membre[1].face[4].bas1.x = -0.125;
    personnage->membre[1].face[4].bas1.y = -0.65;
    personnage->membre[1].face[4].bas1.z = -0.125;

    personnage->membre[1].face[4].bas2.x = -0.125;
    personnage->membre[1].face[4].bas2.y = -0.65;
    personnage->membre[1].face[4].bas2.z = 0.125;

    personnage->membre[1].face[4].haut1.x = 0.125;
    personnage->membre[1].face[4].haut1.y = -0.65;
    personnage->membre[1].face[4].haut1.z = -0.125;

    personnage->membre[1].face[4].haut2.x = 0.125;
    personnage->membre[1].face[4].haut2.y = -0.65;
    personnage->membre[1].face[4].haut2.z = 0.125;

    personnage->tex[10].height = 4;
    personnage->tex[10].weight = 4;
    personnage->tex[10].posTexX = 8;
    personnage->tex[10].posTexY = 16;
    personnage->tex[10].hMax = 32;
    personnage->tex[10].wMax = 64;


    personnage->membre[1].face[5].bas1.x = -0.125;
    personnage->membre[1].face[5].bas1.y = 0;
    personnage->membre[1].face[5].bas1.z = -0.125;

    personnage->membre[1].face[5].bas2.x = -0.125;
    personnage->membre[1].face[5].bas2.y = 0;
    personnage->membre[1].face[5].bas2.z = 0.125;

    personnage->membre[1].face[5].haut1.x = 0.125;
    personnage->membre[1].face[5].haut1.y = 0;
    personnage->membre[1].face[5].haut1.z = -0.125;

    personnage->membre[1].face[5].haut2.x = 0.125;
    personnage->membre[1].face[5].haut2.y = 0;
    personnage->membre[1].face[5].haut2.z = 0.125;

    personnage->tex[11].height = 4;
    personnage->tex[11].weight = 4;
    personnage->tex[11].posTexX = 4;
    personnage->tex[11].posTexY = 16;
    personnage->tex[11].hMax = 32;
    personnage->tex[11].wMax = 64;

    //Torse

    personnage->membre[2].face[0].bas1.x = -0.25;
    personnage->membre[2].face[0].bas1.y = -0.65;
    personnage->membre[2].face[0].bas1.z = -0.125;

    personnage->membre[2].face[0].bas2.x = 0.25;
    personnage->membre[2].face[0].bas2.y = -0.65;
    personnage->membre[2].face[0].bas2.z = -0.125;

    personnage->membre[2].face[0].haut1.x = -0.25;
    personnage->membre[2].face[0].haut1.y = 0;
    personnage->membre[2].face[0].haut1.z = -0.125;

    personnage->membre[2].face[0].haut2.x = 0.25;
    personnage->membre[2].face[0].haut2.y = 0;
    personnage->membre[2].face[0].haut2.z = -0.125;

    personnage->tex[12].height = 12;
    personnage->tex[12].weight = 8;
    personnage->tex[12].posTexX = 20;
    personnage->tex[12].posTexY = 20;
    personnage->tex[12].hMax = 32;
    personnage->tex[12].wMax = 64;


    personnage->membre[2].face[1].bas1.x = -0.25;
    personnage->membre[2].face[1].bas1.y = -0.65;
    personnage->membre[2].face[1].bas1.z = -0.125;

    personnage->membre[2].face[1].bas2.x = -0.25;
    personnage->membre[2].face[1].bas2.y = -0.65;
    personnage->membre[2].face[1].bas2.z = 0.125;

    personnage->membre[2].face[1].haut1.x = -0.25;
    personnage->membre[2].face[1].haut1.y = 0;
    personnage->membre[2].face[1].haut1.z = -0.125;

    personnage->membre[2].face[1].haut2.x = -0.25;
    personnage->membre[2].face[1].haut2.y = 0;
    personnage->membre[2].face[1].haut2.z = 0.125;

    personnage->tex[13].height = 12;
    personnage->tex[13].weight = 4;
    personnage->tex[13].posTexX = 16;
    personnage->tex[13].posTexY = 20;
    personnage->tex[13].hMax = 32;
    personnage->tex[13].wMax = 64;


    personnage->membre[2].face[2].bas1.x = -0.25;
    personnage->membre[2].face[2].bas1.y = -0.65;
    personnage->membre[2].face[2].bas1.z = 0.125;

    personnage->membre[2].face[2].bas2.x = 0.25;
    personnage->membre[2].face[2].bas2.y = -0.65;
    personnage->membre[2].face[2].bas2.z = 0.125;

    personnage->membre[2].face[2].haut1.x = -0.25;
    personnage->membre[2].face[2].haut1.y = 0;
    personnage->membre[2].face[2].haut1.z = 0.125;

    personnage->membre[2].face[2].haut2.x = 0.25;
    personnage->membre[2].face[2].haut2.y = 0;
    personnage->membre[2].face[2].haut2.z = 0.125;

    personnage->tex[14].height = 12;
    personnage->tex[14].weight = 8;
    personnage->tex[14].posTexX = 32;
    personnage->tex[14].posTexY = 20;
    personnage->tex[14].hMax = 32;
    personnage->tex[14].wMax = 64;


    personnage->membre[2].face[3].bas1.x = 0.25;
    personnage->membre[2].face[3].bas1.y = -0.65;
    personnage->membre[2].face[3].bas1.z = 0.125;

    personnage->membre[2].face[3].bas2.x = 0.25;
    personnage->membre[2].face[3].bas2.y = -0.65;
    personnage->membre[2].face[3].bas2.z = -0.125;

    personnage->membre[2].face[3].haut1.x = 0.25;
    personnage->membre[2].face[3].haut1.y = 0;
    personnage->membre[2].face[3].haut1.z = 0.125;

    personnage->membre[2].face[3].haut2.x = 0.25;
    personnage->membre[2].face[3].haut2.y = 0;
    personnage->membre[2].face[3].haut2.z = -0.125;

    personnage->tex[15].height = 12;
    personnage->tex[15].weight = 4;
    personnage->tex[15].posTexX = 28;
    personnage->tex[15].posTexY = 20;
    personnage->tex[15].hMax = 32;
    personnage->tex[15].wMax = 64;


    personnage->membre[2].face[4].bas1.x = -0.25;
    personnage->membre[2].face[4].bas1.y = -0.65;
    personnage->membre[2].face[4].bas1.z = -0.125;

    personnage->membre[2].face[4].bas2.x = -0.25;
    personnage->membre[2].face[4].bas2.y = -0.65;
    personnage->membre[2].face[4].bas2.z = 0.125;

    personnage->membre[2].face[4].haut1.x = 0.25;
    personnage->membre[2].face[4].haut1.y = -0.65;
    personnage->membre[2].face[4].haut1.z = -0.125;

    personnage->membre[2].face[4].haut2.x = 0.25;
    personnage->membre[2].face[4].haut2.y = -0.65;
    personnage->membre[2].face[4].haut2.z = 0.125;

    personnage->tex[16].height = 4;
    personnage->tex[16].weight = 4;
    personnage->tex[16].posTexX = 4;
    personnage->tex[16].posTexY = 16;
    personnage->tex[16].hMax = 32;
    personnage->tex[16].wMax = 64;


    personnage->membre[2].face[5].bas1.x = -0.25;
    personnage->membre[2].face[5].bas1.y = 0;
    personnage->membre[2].face[5].bas1.z = -0.125;

    personnage->membre[2].face[5].bas2.x = -0.25;
    personnage->membre[2].face[5].bas2.y = 0;
    personnage->membre[2].face[5].bas2.z = 0.125;

    personnage->membre[2].face[5].haut1.x = 0.25;
    personnage->membre[2].face[5].haut1.y = 0;
    personnage->membre[2].face[5].haut1.z = -0.125;

    personnage->membre[2].face[5].haut2.x = 0.25;
    personnage->membre[2].face[5].haut2.y = 0;
    personnage->membre[2].face[5].haut2.z = 0.125;

    personnage->tex[17].height = 4;
    personnage->tex[17].weight = 8;
    personnage->tex[17].posTexX = 28;
    personnage->tex[17].posTexY = 16;
    personnage->tex[17].hMax = 32;
    personnage->tex[17].wMax = 64;

    //tête

    personnage->membre[3].face[0].bas1.x = -0.225;
    personnage->membre[3].face[0].bas1.y = 0;
    personnage->membre[3].face[0].bas1.z = -0.225;

    personnage->membre[3].face[0].bas2.x = 0.225;
    personnage->membre[3].face[0].bas2.y = 0;
    personnage->membre[3].face[0].bas2.z = -0.225;

    personnage->membre[3].face[0].haut1.x = -0.225;
    personnage->membre[3].face[0].haut1.y = 0.45;
    personnage->membre[3].face[0].haut1.z = -0.225;

    personnage->membre[3].face[0].haut2.x = 0.225;
    personnage->membre[3].face[0].haut2.y = 0.45;
    personnage->membre[3].face[0].haut2.z = -0.225;

    personnage->tex[18].height = 8;
    personnage->tex[18].weight = 8;
    personnage->tex[18].posTexX = 8;
    personnage->tex[18].posTexY = 8;
    personnage->tex[18].hMax = 32;
    personnage->tex[18].wMax = 64;


    personnage->membre[3].face[1].bas1.x = -0.225;
    personnage->membre[3].face[1].bas1.y = 0;
    personnage->membre[3].face[1].bas1.z = -0.225;

    personnage->membre[3].face[1].bas2.x = -0.225;
    personnage->membre[3].face[1].bas2.y = 0;
    personnage->membre[3].face[1].bas2.z = 0.225;

    personnage->membre[3].face[1].haut1.x = -0.225;
    personnage->membre[3].face[1].haut1.y = 0.45;
    personnage->membre[3].face[1].haut1.z = -0.225;

    personnage->membre[3].face[1].haut2.x = -0.225;
    personnage->membre[3].face[1].haut2.y = 0.45;
    personnage->membre[3].face[1].haut2.z = 0.225;

    personnage->tex[19].height = 8;
    personnage->tex[19].weight = 8;
    personnage->tex[19].posTexX = 0;
    personnage->tex[19].posTexY = 8;
    personnage->tex[19].hMax = 32;
    personnage->tex[19].wMax = 64;


    personnage->membre[3].face[2].bas1.x = -0.225;
    personnage->membre[3].face[2].bas1.y = 0;
    personnage->membre[3].face[2].bas1.z = 0.225;

    personnage->membre[3].face[2].bas2.x = 0.225;
    personnage->membre[3].face[2].bas2.y = 0;
    personnage->membre[3].face[2].bas2.z = 0.225;

    personnage->membre[3].face[2].haut1.x = -0.225;
    personnage->membre[3].face[2].haut1.y = 0.45;
    personnage->membre[3].face[2].haut1.z = 0.225;

    personnage->membre[3].face[2].haut2.x = 0.225;
    personnage->membre[3].face[2].haut2.y = 0.45;
    personnage->membre[3].face[2].haut2.z = 0.225;

    personnage->tex[20].height = 8;
    personnage->tex[20].weight = 8;
    personnage->tex[20].posTexX = 24;
    personnage->tex[20].posTexY = 8;
    personnage->tex[20].hMax = 32;
    personnage->tex[20].wMax = 64;


    personnage->membre[3].face[3].bas1.x = 0.225;
    personnage->membre[3].face[3].bas1.y = 0;
    personnage->membre[3].face[3].bas1.z = 0.225;

    personnage->membre[3].face[3].bas2.x = 0.225;
    personnage->membre[3].face[3].bas2.y = 0;
    personnage->membre[3].face[3].bas2.z = -0.225;

    personnage->membre[3].face[3].haut1.x = 0.225;
    personnage->membre[3].face[3].haut1.y = 0.45;
    personnage->membre[3].face[3].haut1.z = 0.225;

    personnage->membre[3].face[3].haut2.x = 0.225;
    personnage->membre[3].face[3].haut2.y = 0.45;
    personnage->membre[3].face[3].haut2.z = -0.225;

    personnage->tex[21].height = 8;
    personnage->tex[21].weight = 8;
    personnage->tex[21].posTexX = 16;
    personnage->tex[21].posTexY = 8;
    personnage->tex[21].hMax = 32;
    personnage->tex[21].wMax = 64;


    personnage->membre[3].face[4].bas1.x = -0.225;
    personnage->membre[3].face[4].bas1.y = 0;
    personnage->membre[3].face[4].bas1.z = -0.225;

    personnage->membre[3].face[4].bas2.x = -0.225;
    personnage->membre[3].face[4].bas2.y = 0;
    personnage->membre[3].face[4].bas2.z = 0.225;

    personnage->membre[3].face[4].haut1.x = 0.225;
    personnage->membre[3].face[4].haut1.y = 0;
    personnage->membre[3].face[4].haut1.z = -0.225;

    personnage->membre[3].face[4].haut2.x = 0.225;
    personnage->membre[3].face[4].haut2.y = 0;
    personnage->membre[3].face[4].haut2.z = 0.225;

    personnage->tex[22].height = 8;
    personnage->tex[22].weight = 8;
    personnage->tex[22].posTexX = 16;
    personnage->tex[22].posTexY = 0;
    personnage->tex[22].hMax = 32;
    personnage->tex[22].wMax = 64;


    personnage->membre[3].face[5].bas1.x = -0.225;
    personnage->membre[3].face[5].bas1.y = 0.45;
    personnage->membre[3].face[5].bas1.z = -0.225;

    personnage->membre[3].face[5].bas2.x = -0.225;
    personnage->membre[3].face[5].bas2.y = 0.45;
    personnage->membre[3].face[5].bas2.z = 0.225;

    personnage->membre[3].face[5].haut1.x = 0.225;
    personnage->membre[3].face[5].haut1.y = 0.45;
    personnage->membre[3].face[5].haut1.z = -0.225;

    personnage->membre[3].face[5].haut2.x = 0.225;
    personnage->membre[3].face[5].haut2.y = 0.45;
    personnage->membre[3].face[5].haut2.z = 0.225;

    personnage->tex[23].height = 8;
    personnage->tex[23].weight = 8;
    personnage->tex[23].posTexX = 8;
    personnage->tex[23].posTexY = 0;
    personnage->tex[23].hMax = 32;
    personnage->tex[23].wMax = 64;


    //Bras gauche
    personnage->membre[4].face[0].bas1.x = -0.125;
    personnage->membre[4].face[0].bas1.y = -0.65;
    personnage->membre[4].face[0].bas1.z = -0.125;

    personnage->membre[4].face[0].bas2.x = 0.125;
    personnage->membre[4].face[0].bas2.y = -0.65;
    personnage->membre[4].face[0].bas2.z = -0.125;

    personnage->membre[4].face[0].haut1.x = -0.125;
    personnage->membre[4].face[0].haut1.y = 0;
    personnage->membre[4].face[0].haut1.z = -0.125;

    personnage->membre[4].face[0].haut2.x = 0.125;
    personnage->membre[4].face[0].haut2.y = 0;
    personnage->membre[4].face[0].haut2.z = -0.125;

    personnage->tex[24].height = 12;
    personnage->tex[24].weight = 4;
    personnage->tex[24].posTexX = 44;
    personnage->tex[24].posTexY = 20;
    personnage->tex[24].hMax = 32;
    personnage->tex[24].wMax = 64;


    personnage->membre[4].face[1].bas1.x = -0.125;
    personnage->membre[4].face[1].bas1.y = -0.65;
    personnage->membre[4].face[1].bas1.z = -0.125;

    personnage->membre[4].face[1].bas2.x = -0.125;
    personnage->membre[4].face[1].bas2.y = -0.65;
    personnage->membre[4].face[1].bas2.z = 0.125;

    personnage->membre[4].face[1].haut1.x = -0.125;
    personnage->membre[4].face[1].haut1.y = 0;
    personnage->membre[4].face[1].haut1.z = -0.125;

    personnage->membre[4].face[1].haut2.x = -0.125;
    personnage->membre[4].face[1].haut2.y = 0;
    personnage->membre[4].face[1].haut2.z = 0.125;

    personnage->tex[25].height = 12;
    personnage->tex[25].weight = 4;
    personnage->tex[25].posTexX = 40;
    personnage->tex[25].posTexY = 20;
    personnage->tex[25].hMax = 32;
    personnage->tex[25].wMax = 64;


    personnage->membre[4].face[2].bas1.x = -0.125;
    personnage->membre[4].face[2].bas1.y = -0.65;
    personnage->membre[4].face[2].bas1.z = 0.125;

    personnage->membre[4].face[2].bas2.x = 0.125;
    personnage->membre[4].face[2].bas2.y = -0.65;
    personnage->membre[4].face[2].bas2.z = 0.125;

    personnage->membre[4].face[2].haut1.x = -0.125;
    personnage->membre[4].face[2].haut1.y = 0;
    personnage->membre[4].face[2].haut1.z = 0.125;

    personnage->membre[4].face[2].haut2.x = 0.125;
    personnage->membre[4].face[2].haut2.y = 0;
    personnage->membre[4].face[2].haut2.z = 0.125;

    personnage->tex[26].height = 12;
    personnage->tex[26].weight = 4;
    personnage->tex[26].posTexX = 52;
    personnage->tex[26].posTexY = 20;
    personnage->tex[26].hMax = 32;
    personnage->tex[26].wMax = 64;

    personnage->membre[4].face[3].bas1.x = 0.125;
    personnage->membre[4].face[3].bas1.y = -0.65;
    personnage->membre[4].face[3].bas1.z = 0.125;

    personnage->membre[4].face[3].bas2.x = 0.125;
    personnage->membre[4].face[3].bas2.y = -0.65;
    personnage->membre[4].face[3].bas2.z = -0.125;

    personnage->membre[4].face[3].haut1.x = 0.125;
    personnage->membre[4].face[3].haut1.y = 0;
    personnage->membre[4].face[3].haut1.z = 0.125;

    personnage->membre[4].face[3].haut2.x = 0.125;
    personnage->membre[4].face[3].haut2.y = 0;
    personnage->membre[4].face[3].haut2.z = -0.125;

    personnage->tex[27].height = 12;
    personnage->tex[27].weight = 4;
    personnage->tex[27].posTexX = 48;
    personnage->tex[27].posTexY = 20;
    personnage->tex[27].hMax = 32;
    personnage->tex[27].wMax = 64;


    personnage->membre[4].face[4].bas1.x = -0.125;
    personnage->membre[4].face[4].bas1.y = -0.65;
    personnage->membre[4].face[4].bas1.z = -0.125;

    personnage->membre[4].face[4].bas2.x = -0.125;
    personnage->membre[4].face[4].bas2.y = -0.65;
    personnage->membre[4].face[4].bas2.z = 0.125;

    personnage->membre[4].face[4].haut1.x = 0.125;
    personnage->membre[4].face[4].haut1.y = -0.65;
    personnage->membre[4].face[4].haut1.z = -0.125;

    personnage->membre[4].face[4].haut2.x = 0.125;
    personnage->membre[4].face[4].haut2.y = -0.65;
    personnage->membre[4].face[4].haut2.z = 0.125;

    personnage->tex[28].height = 4;
    personnage->tex[28].weight = 4;
    personnage->tex[28].posTexX = 48;
    personnage->tex[28].posTexY = 16;
    personnage->tex[28].hMax = 32;
    personnage->tex[28].wMax = 64;


    personnage->membre[4].face[5].bas1.x = -0.125;
    personnage->membre[4].face[5].bas1.y = 0;
    personnage->membre[4].face[5].bas1.z = -0.125;

    personnage->membre[4].face[5].bas2.x = -0.125;
    personnage->membre[4].face[5].bas2.y = 0;
    personnage->membre[4].face[5].bas2.z = 0.125;

    personnage->membre[4].face[5].haut1.x = 0.125;
    personnage->membre[4].face[5].haut1.y = 0;
    personnage->membre[4].face[5].haut1.z = -0.125;

    personnage->membre[4].face[5].haut2.x = 0.125;
    personnage->membre[4].face[5].haut2.y = 0;
    personnage->membre[4].face[5].haut2.z = 0.125;

    personnage->tex[29].height = 4;
    personnage->tex[29].weight = 4;
    personnage->tex[29].posTexX = 44;
    personnage->tex[29].posTexY = 16;
    personnage->tex[29].hMax = 32;
    personnage->tex[29].wMax = 64;


    //Bras droit
    personnage->membre[5].face[0].bas1.x = -0.125;
    personnage->membre[5].face[0].bas1.y = -0.65;
    personnage->membre[5].face[0].bas1.z = -0.125;

    personnage->membre[5].face[0].bas2.x = 0.125;
    personnage->membre[5].face[0].bas2.y = -0.65;
    personnage->membre[5].face[0].bas2.z = -0.125;

    personnage->membre[5].face[0].haut1.x = -0.125;
    personnage->membre[5].face[0].haut1.y = 0;
    personnage->membre[5].face[0].haut1.z = -0.125;

    personnage->membre[5].face[0].haut2.x = 0.125;
    personnage->membre[5].face[0].haut2.y = 0;
    personnage->membre[5].face[0].haut2.z = -0.125;

    personnage->tex[30].height = 12;
    personnage->tex[30].weight = 4;
    personnage->tex[30].posTexX = 44;
    personnage->tex[30].posTexY = 20;
    personnage->tex[30].hMax = 32;
    personnage->tex[30].wMax = 64;


    personnage->membre[5].face[1].bas1.x = -0.125;
    personnage->membre[5].face[1].bas1.y = -0.65;
    personnage->membre[5].face[1].bas1.z = -0.125;

    personnage->membre[5].face[1].bas2.x = -0.125;
    personnage->membre[5].face[1].bas2.y = -0.65;
    personnage->membre[5].face[1].bas2.z = 0.125;

    personnage->membre[5].face[1].haut1.x = -0.125;
    personnage->membre[5].face[1].haut1.y = 0;
    personnage->membre[5].face[1].haut1.z = -0.125;

    personnage->membre[5].face[1].haut2.x = -0.125;
    personnage->membre[5].face[1].haut2.y = 0;
    personnage->membre[5].face[1].haut2.z = 0.125;

    personnage->tex[31].height = 12;
    personnage->tex[31].weight = 4;
    personnage->tex[31].posTexX = 48;
    personnage->tex[31].posTexY = 20;
    personnage->tex[31].hMax = 32;
    personnage->tex[31].wMax = 64;


    personnage->membre[5].face[2].bas1.x = -0.125;
    personnage->membre[5].face[2].bas1.y = -0.65;
    personnage->membre[5].face[2].bas1.z = 0.125;

    personnage->membre[5].face[2].bas2.x = 0.125;
    personnage->membre[5].face[2].bas2.y = -0.65;
    personnage->membre[5].face[2].bas2.z = 0.125;

    personnage->membre[5].face[2].haut1.x = -0.125;
    personnage->membre[5].face[2].haut1.y = 0;
    personnage->membre[5].face[2].haut1.z = 0.125;

    personnage->membre[5].face[2].haut2.x = 0.125;
    personnage->membre[5].face[2].haut2.y = 0;
    personnage->membre[5].face[2].haut2.z = 0.125;

    personnage->tex[32].height = 12;
    personnage->tex[32].weight = 4;
    personnage->tex[32].posTexX = 52;
    personnage->tex[32].posTexY = 20;
    personnage->tex[32].hMax = 32;
    personnage->tex[32].wMax = 64;


    personnage->membre[5].face[3].bas1.x = 0.125;
    personnage->membre[5].face[3].bas1.y = -0.65;
    personnage->membre[5].face[3].bas1.z = 0.125;

    personnage->membre[5].face[3].bas2.x = 0.125;
    personnage->membre[5].face[3].bas2.y = -0.65;
    personnage->membre[5].face[3].bas2.z = -0.125;

    personnage->membre[5].face[3].haut1.x = 0.125;
    personnage->membre[5].face[3].haut1.y = 0;
    personnage->membre[5].face[3].haut1.z = 0.125;

    personnage->membre[5].face[3].haut2.x = 0.125;
    personnage->membre[5].face[3].haut2.y = 0;
    personnage->membre[5].face[3].haut2.z = -0.125;

    personnage->tex[33].height = 12;
    personnage->tex[33].weight = 4;
    personnage->tex[33].posTexX = 40;
    personnage->tex[33].posTexY = 20;
    personnage->tex[33].hMax = 32;
    personnage->tex[33].wMax = 64;


    personnage->membre[5].face[4].bas1.x = -0.125;
    personnage->membre[5].face[4].bas1.y = -0.65;
    personnage->membre[5].face[4].bas1.z = -0.125;

    personnage->membre[5].face[4].bas2.x = -0.125;
    personnage->membre[5].face[4].bas2.y = -0.65;
    personnage->membre[5].face[4].bas2.z = 0.125;

    personnage->membre[5].face[4].haut1.x = 0.125;
    personnage->membre[5].face[4].haut1.y = -0.65;
    personnage->membre[5].face[4].haut1.z = -0.125;

    personnage->membre[5].face[4].haut2.x = 0.125;
    personnage->membre[5].face[4].haut2.y = -0.65;
    personnage->membre[5].face[4].haut2.z = 0.125;

    personnage->tex[34].height = 4;
    personnage->tex[34].weight = 4;
    personnage->tex[34].posTexX = 48;
    personnage->tex[34].posTexY = 16;
    personnage->tex[34].hMax = 32;
    personnage->tex[34].wMax = 64;


    personnage->membre[5].face[5].bas1.x = -0.125;
    personnage->membre[5].face[5].bas1.y = 0;
    personnage->membre[5].face[5].bas1.z = -0.125;

    personnage->membre[5].face[5].bas2.x = -0.125;
    personnage->membre[5].face[5].bas2.y = 0;
    personnage->membre[5].face[5].bas2.z = 0.125;

    personnage->membre[5].face[5].haut1.x = 0.125;
    personnage->membre[5].face[5].haut1.y = 0;
    personnage->membre[5].face[5].haut1.z = -0.125;

    personnage->membre[5].face[5].haut2.x = 0.125;
    personnage->membre[5].face[5].haut2.y = 0;
    personnage->membre[5].face[5].haut2.z = 0.125;

    personnage->tex[35].height = 4;
    personnage->tex[35].weight = 4;
    personnage->tex[35].posTexX = 44;
    personnage->tex[35].posTexY = 16;
    personnage->tex[35].hMax = 32;
    personnage->tex[35].wMax = 64;
}

void dessinerPersonnage(Mob personnage, double angleMembres, double angleTeteY, double angleTeteX)
{
    int i, j, n;

    for(i = 0; i < 6; i++)//partie du corps
    {
        glPushMatrix();
        if(i == 0)
        {
            glTranslated(-0.125, 0.65, 0);
            glRotated(-angleMembres, 1, 0, 0);
        }
        if(i == 1)
        {
            glTranslated(0.125, 0.65, 0);
            glRotated(angleMembres, 1, 0, 0);
        }
        if(i == 2)
        {
            glTranslated(0, 1.3, 0);
        }
        if(i == 3)
        {
            glTranslated(0, 1.3, 0);
            glRotated(180 + angleTeteY, 0, 1, 0);
            glRotated(-angleTeteX + 90, 1, 0, 0);
        }
        if(i == 4)
        {
            glTranslated(0.375, 1.3, 0);
            glRotated(-angleMembres, 1, 0, 0);
        }
        if(i == 5)
        {
            glTranslated(-0.375, 1.3, 0);
            glRotated(angleMembres, 1, 0, 0);
        }
        for(j = 0; j < 6; j++)//face des parties
        {
            n = 6 * i + j;
            glBindTexture(GL_TEXTURE_2D, personnage.tex[i].IDtex);
            glBegin(GL_QUADS);
            glTexCoord2d((double)personnage.tex[n].posTexX / personnage.tex[n].wMax, (double)(personnage.tex[n].hMax - personnage.tex[n].posTexY) / personnage.tex[n].hMax);
            afficherPoint(personnage.membre[i].face[j].haut2);
            glTexCoord2d((double)(personnage.tex[n].posTexX + personnage.tex[n].weight) / personnage.tex[n].wMax, (double)(personnage.tex[n].hMax - personnage.tex[n].posTexY) / personnage.tex[n].hMax);
            afficherPoint(personnage.membre[i].face[j].haut1);
            glTexCoord2d((double)(personnage.tex[n].posTexX + personnage.tex[n].weight) / personnage.tex[n].wMax, (double)(personnage.tex[n].hMax - personnage.tex[n].posTexY - personnage.tex[n].height) / personnage.tex[n].hMax);
            afficherPoint(personnage.membre[i].face[j].bas1);
            glTexCoord2d((double)personnage.tex[n].posTexX / personnage.tex[n].wMax, (double)(personnage.tex[n].hMax - personnage.tex[n].posTexY - personnage.tex[n].height) / personnage.tex[n].hMax);
            afficherPoint(personnage.membre[i].face[j].bas2);
            glEnd();
        }
        glPopMatrix();
    }
}

void chargerItems(Item *items, char *chemin)
{
    FILE *fichier = NULL;
    int i;

    fichier = fopen(chemin, "r");

    if(fichier != NULL)
    {
        for(i = 0; i < NOMBRE_ITEMS; i++)
        {
            fscanf(fichier, "%d\n", &items[i].ID);
            fscanf(fichier, "%d\n", &items[i].IDTex);
        }
    }
    else
        printf("Impossible d'ouvrir le fichier : %s\n", chemin);

    fclose(fichier);
}
