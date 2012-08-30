#include "constantes.h"
#include "input.h"
#include "texte.h"
#include "jeu.h"

Texture texTexte;
extern Input event;

void saisirTexte(char texte[])
{
    int curseur = 0;
    int tpsActuel = 0, tpsPrecedent = 0;
    char c = 0;

    while(event.touche[SDLK_RETURN] == 0 && event.touche[SDLK_KP_ENTER] == 0)
    {
        updateEvents(&event);

        tpsActuel = SDL_GetTicks();

        if(tpsActuel > tpsPrecedent + 20)
        {

            c = interpreterEvent();

            if(c != 0)
            {
                texte[curseur] = c;
                curseur++;
                c = 0;
            }

            if(event.touche[SDLK_BACKSPACE] == 1)
            {
                if(curseur > 0)
                {
                    curseur--;
                    texte[curseur] = 0;
                }
                event.touche[SDLK_BACKSPACE] = 0;
            }
            tpsPrecedent = tpsActuel;
        }
        printf("Actuel (%d) : %s_\n", tpsActuel, texte);
    }
}

char interpreterEvent()
{
    int i;
    char c = 0;

    for(i = 0; i < SDLK_LAST; i++)
    {
        if(event.toucheUni[i] == 1)
        {
            if(i != 0 && i != SDLK_BACKSPACE && i != SDLK_ESCAPE)
            {
                c = i;

                event.toucheUni[i] = 0;
            }
        }
    }

    return c;
}

void afficherTexte(GLuint texture, Texte texte, int *largeurLettre, double taillePolice, int x, int y)
{
    int posX, posY;
    int i;

    texTexte.IDtex = texture;
    texTexte.weight = 0;
    texTexte.height = 16;
    texTexte.wMax = 256;
    texTexte.hMax = 256;

    glPushMatrix();

    texTexte.posX = x;
    texTexte.posY = y + 2;

    glColor3ub(50, 50, 50);

    for(i = 0; i < texte.nbCara; i++)
    {
        posY = texte.chaine[i] / 16;
        posX = texte.chaine[i] - posY * 16;

        texTexte.posTexX = posX * 16;
        texTexte.posTexY = posY * 16;

        texTexte.posX += texTexte.weight + 2;

        texTexte.weight = largeurLettre[(int)texte.chaine[i]];

        texTexte.posX += 2;

        if(texte.chaine[i] != ' ' && texte.chaine[i] != 0)
        {
            glEnable(GL_BLEND);
            glBindTexture(GL_TEXTURE_2D, texTexte.IDtex);

            glBegin(GL_QUADS);
            glTexCoord2d((double)texTexte.posTexX / texTexte.wMax, (double)(texTexte.hMax - texTexte.posTexY) / texTexte.hMax);
            glVertex2d(texTexte.posX, FENETRE_HAUT - texTexte.posY);
            glTexCoord2d((double)(texTexte.posTexX + texTexte.weight) / texTexte.wMax, (double)(texTexte.hMax - texTexte.posTexY) / texTexte.hMax);
            glVertex2d(texTexte.posX + (texTexte.weight * taillePolice), FENETRE_HAUT - texTexte.posY);
            glTexCoord2d((double)(texTexte.posTexX + texTexte.weight) / texTexte.wMax, (double)(texTexte.hMax - (texTexte.posTexY + texTexte.height)) / texTexte.hMax);
            glVertex2d(texTexte.posX + (texTexte.weight * taillePolice), (FENETRE_HAUT - texTexte.posY) - (texTexte.height * taillePolice));
            glTexCoord2d((double)(texTexte.posTexX) / texTexte.wMax, (double)(texTexte.hMax - (texTexte.posTexY + texTexte.height)) / texTexte.hMax);
            glVertex2d(texTexte.posX, (FENETRE_HAUT - texTexte.posY) - (texTexte.height * taillePolice));
            glEnd();

            glDisable(GL_BLEND);
        }

        texTexte.posX -= 2;
    }

    glTranslated(0, 0, 1);
    glColor3ub(255, 255, 255);

    texTexte.posX = x;
    texTexte.posY = y;
    texTexte.weight = 0;

    for(i = 0; i < texte.nbCara; i++)
    {
        posY = texte.chaine[i] / 16;
        posX = texte.chaine[i] - posY * 16;

        texTexte.posTexX = posX * 16;
        texTexte.posTexY = posY * 16;

        texTexte.posX += texTexte.weight + 2;

        texTexte.weight = largeurLettre[(int)texte.chaine[i]];

        if(texte.chaine[i] != ' ' && texte.chaine[i] != 0)
        {
            glEnable(GL_BLEND);
            glBindTexture(GL_TEXTURE_2D, texTexte.IDtex);

            glBegin(GL_QUADS);
            glTexCoord2d((double)texTexte.posTexX / texTexte.wMax, (double)(texTexte.hMax - texTexte.posTexY) / texTexte.hMax);
            glVertex2d(texTexte.posX, FENETRE_HAUT - texTexte.posY);
            glTexCoord2d((double)(texTexte.posTexX + texTexte.weight) / texTexte.wMax, (double)(texTexte.hMax - texTexte.posTexY) / texTexte.hMax);
            glVertex2d(texTexte.posX + (texTexte.weight * taillePolice), FENETRE_HAUT - texTexte.posY);
            glTexCoord2d((double)(texTexte.posTexX + texTexte.weight) / texTexte.wMax, (double)(texTexte.hMax - (texTexte.posTexY + texTexte.height)) / texTexte.hMax);
            glVertex2d(texTexte.posX + (texTexte.weight * taillePolice), (FENETRE_HAUT - texTexte.posY) - (texTexte.height * taillePolice));
            glTexCoord2d((double)(texTexte.posTexX) / texTexte.wMax, (double)(texTexte.hMax - (texTexte.posTexY + texTexte.height)) / texTexte.hMax);
            glVertex2d(texTexte.posX, (FENETRE_HAUT - texTexte.posY) - (texTexte.height * taillePolice));
            glEnd();

            glDisable(GL_BLEND);
        }
    }

    glPopMatrix();
}

void chargerLargeurLettres(char *chemin, int largeurLettre[255])
{
    FILE *fichier = NULL;
    int n, i;

    fichier = fopen(chemin, "r");

    if(fichier != NULL)
    {
        for(i = 0; n != EOF && i < 255; i++)
        {
            fscanf(fichier, "width.%d=", &n);
            fscanf(fichier, "%d\n", &largeurLettre[n]);
        }
    }
    else
        printf("Impossible d'ouvrir le fichier %s.\n", chemin);

    for(i = 0; i < 255; i++)
    {
        if(largeurLettre[i] == 2)
            largeurLettre[i] = 2;
        else if(largeurLettre[i] == 3)
            largeurLettre[i] = 4;
        else if(largeurLettre[i] == 4)
            largeurLettre[i] = 6;
        else if(largeurLettre[i] == 5)
            largeurLettre[i] = 8;
        else if(largeurLettre[i] == 6)
            largeurLettre[i] = 10;
        else if(largeurLettre[i] == 7)
            largeurLettre[i] = 12;
        else if(largeurLettre[i] == 8)
            largeurLettre[i] = 8;
    }

    largeurLettre[32] = 5;

    fclose(fichier);
}
