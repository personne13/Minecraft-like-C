#include "constantes.h"
#include "map.h"
#include "input.h"
#include "jeu.h"

extern Pave cube[NOMBRE_ENTITE];

int chargerBlocs(char *chemin, Pave *bloc, int nombreBlocs)//Chargement des textures des blocs à l'aide du fichier "bloc.info"
{
    FILE *fichier = NULL;
    int i;
    double versionFichier = 0, versionActuelle = 0.01;

    fichier = fopen(chemin, "r+");

    if(fichier != NULL)
    {
        fscanf(fichier, "%lf", &versionFichier);
        if(versionFichier == versionActuelle)
        {
            for(i = 0; i < nombreBlocs; i++)
            {
                fscanf(fichier, "%d", &bloc[i].ID);
                fgetc(fichier);
                fscanf(fichier, "%d %d %d %d %d %d", &bloc[i].face[0].IdTexture, &bloc[i].face[1].IdTexture, &bloc[i].face[2].IdTexture, &bloc[i].face[3].IdTexture, &bloc[i].face[4].IdTexture, &bloc[i].face[5].IdTexture);
            }
        }
        else
        {
            printf("Fichier \"bloc.info\" pas a jour (version %lf actuelle)\n", versionActuelle);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Fichier non existant : %s\n", chemin);
        exit(EXIT_FAILURE);
    }
    fclose(fichier);

    return 1;
}

void dessinerChunk(Chunk *chunk, GLuint texture)
{
    static int x, y, z, i;
    static char facesAffichables[6] = {1, 1, 1, 1, 1, 1};

    glBindTexture(GL_TEXTURE_2D, texture);

    glColor3ub(178, 178, 178);

    for(y = 0; y < TAILLECHUNK_Y && y < chunk->hauteurMax; y++)
    {
        for(x = 0; x < TAILLECHUNK_X; x++)
        {
            for(z = 0; z < TAILLECHUNK_Z; z++)
            {
                if(chunk->entite[x][y][z] != 0 && chunk->entite[x][y][z] != 20 && chunk->entite[x][y][z] != 18)//Affichage des blocs non-transparents
                {
                    glPushMatrix();
                    glTranslated(x, y, z);

                    if(z > 0)
                    {
                        if(chunk->entite[x][y][z - 1] != 0 && chunk->entite[x][y][z - 1] != 20 && chunk->entite[x][y + 1][z] != 18)
                        {
                            facesAffichables[0] = 0;
                        }
                    }
                    if(x > 0)
                    {
                        if(chunk->entite[x - 1][y][z] != 0 && chunk->entite[x - 1][y][z] != 20 && chunk->entite[x][y + 1][z] != 18)
                        {
                            facesAffichables[1] = 0;
                        }
                    }
                    if(z + 1 < TAILLECHUNK_Z)
                    {
                        if(chunk->entite[x][y][z + 1] != 0 && chunk->entite[x][y][z + 1] != 20 && chunk->entite[x][y + 1][z] != 18)
                        {
                            facesAffichables[2] = 0;
                        }
                    }
                    if(x + 1 < TAILLECHUNK_X)
                    {
                        if(chunk->entite[x + 1][y][z] != 0 && chunk->entite[x + 1][y][z] != 20 && chunk->entite[x][y + 1][z] != 18)
                        {
                            facesAffichables[3] = 0;
                        }
                    }
                    if(y > 0)
                    {
                        if(chunk->entite[x][y - 1][z] != 0 && chunk->entite[x][y - 1][z] != 20 && chunk->entite[x][y + 1][z] != 18)
                        {
                            facesAffichables[4] = 0;
                        }
                    }
                    if(y + 1 < TAILLECHUNK_Y)
                    {
                        if(chunk->entite[x][y + 1][z] != 0 && chunk->entite[x][y + 1][z] != 20 && chunk->entite[x][y + 1][z] != 18)
                        {
                            facesAffichables[5] = 0;
                        }
                    }

                    dessinerCube(chunk->entite[x][y][z], facesAffichables);

                    for(i = 0; i < 6; i++)
                    {
                        facesAffichables[i] = 1;
                    }
                    glPopMatrix();
                }
            }
        }
    }

    for(y = 0; y < TAILLECHUNK_Y && y < chunk->hauteurMax; y++)
    {
        for(x = 0; x < TAILLECHUNK_X; x++)
        {
            for(z = 0; z < TAILLECHUNK_Z; z++)
            {
                if(chunk->entite[x][y][z] == 20 || chunk->entite[x][y][z] == 18)//Affichage des blocs transparents (séparation par soucis du rendu)
                {
                    glPushMatrix();
                    glTranslated(x, y, z);

                    if(z > 0)
                    {
                        if(chunk->entite[x][y][z - 1] != 0)
                        {
                            facesAffichables[0] = 0;
                        }
                    }
                    if(x > 0)
                    {
                        if(chunk->entite[x - 1][y][z] != 0)
                        {
                            facesAffichables[1] = 0;
                        }
                    }
                    if(z + 1 < TAILLECHUNK_Z)
                    {
                        if(chunk->entite[x][y][z + 1] != 0)
                        {
                            facesAffichables[2] = 0;
                        }
                    }
                    if(x + 1 < TAILLECHUNK_X)
                    {
                        if(chunk->entite[x + 1][y][z] != 0)
                        {
                            facesAffichables[3] = 0;
                        }
                    }
                    if(y > 0)
                    {
                        if(chunk->entite[x][y - 1][z] != 0)
                        {
                            facesAffichables[4] = 0;
                        }
                    }
                    if(y + 1 < TAILLECHUNK_Y)
                    {
                        if(chunk->entite[x][y + 1][z] != 0)
                        {
                            facesAffichables[5] = 0;
                        }
                    }

                    dessinerCube(chunk->entite[x][y][z], facesAffichables);;

                    for(i = 0; i < 6; i++)
                    {
                        facesAffichables[i] = 1;
                    }

                    glPopMatrix();
                }
            }
        }
    }
}

void sauvegarderMapF(char *chemin, Chunk terrain)
{
    FILE *fichier = NULL;
    int x, y, z;

    fichier = fopen(chemin, "w+");

    for(y = 0; y < TAILLECHUNK_Y; y++)
    {
        for(x = 0; x < TAILLECHUNK_X; x++)
        {
            for(z = 0; z < TAILLECHUNK_Z; z++)
            {
                fprintf(fichier, "%d ", terrain.entite[x][y][z]);
            }
        }
        fprintf(fichier, "\n");
    }
    fprintf(fichier, "\n");

    fclose(fichier);
}

void dessinerCube(int IDbloc, char facesAffichables[6])//Dessine un seul cube
{
    static int i, xTex, yTex;
    static double posTexture[4] = {0.0};
    static GLfloat transparent[] = {1.0f, 1.0f, 1.0f, 0.0f};
    static GLfloat vert[] = {(float)60/255, (float)179/255, (float)40/255};

    glEnable(GL_BLEND);
    glBegin(GL_QUADS);
    glColor4fv(transparent);
    glColor3ub(200, 200, 200);

    for(i = 0; i < 6; i++)
    {
        if(facesAffichables[i] == 1)
        {
            if(IDbloc != 0)
            {
                yTex = cube[IDbloc - 1].face[i].IdTexture / 16;
                xTex = cube[IDbloc - 1].face[i].IdTexture - (16 * yTex);

                posTexture[0] = (double)xTex / (double)16.0;
                posTexture[1] = (double)(xTex + 1) / (double)16.0;
                posTexture[2] = (double)(16 - (yTex + 1)) / (double)16.0;
                posTexture[3] = (double)(16 - yTex) / (double)16.0;

                if(IDbloc == 18 || (IDbloc == 2 && i == 5))
                    glColor3fv(vert);
            }
            else
            {
                glColor3ub(255 - i * 20, 255 - i * 20, 255 - i * 20);
            }

            glTexCoord2d(posTexture[0], posTexture[2]);
            glVertex3d(cube[IDbloc - 1].face[i].bas1.x, cube[IDbloc - 1].face[i].bas1.y, cube[IDbloc - 1].face[i].bas1.z);
            glTexCoord2d(posTexture[1], posTexture[2]);
            glVertex3d(cube[IDbloc - 1].face[i].bas2.x, cube[IDbloc - 1].face[i].bas2.y, cube[IDbloc - 1].face[i].bas2.z);
            glTexCoord2d(posTexture[1], posTexture[3]);
            glVertex3d(cube[IDbloc - 1].face[i].haut2.x, cube[IDbloc - 1].face[i].haut2.y, cube[IDbloc - 1].face[i].haut2.z);
            glTexCoord2d(posTexture[0], posTexture[3]);
            glVertex3d(cube[IDbloc - 1].face[i].haut1.x, cube[IDbloc - 1].face[i].haut1.y, cube[IDbloc - 1].face[i].haut1.z);
        }
    }

    glEnd();

    glDisable(GL_BLEND);
}

void dessinerCubeVBO(GLuint *CubeBuffers)
{


    glBindBuffer(GL_ARRAY_BUFFER, CubeBuffers[0]);
    glVertexPointer( 3, GL_FLOAT, 6 * sizeof(float), ((float*)NULL + (3)) );
    glColorPointer( 3, GL_FLOAT, 6 * sizeof(float), 0 );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeBuffers[1]);

    //Activation d'utilisation des tableaux
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    // Rendu de notre géométrie
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

}

void initChunk(Chunk *chunk)//Met le tableau à zéro
{
    int x, y, z;

    chunk->hauteurMax = 0;
    chunk->posX = 0;
    chunk->posZ = 0;
    chunk->modifie = 0;

    for(x = 0; x < TAILLECHUNK_X; x++)
    {
        for(y = 0; y < TAILLECHUNK_Y; y++)
        {
            for(z = 0; z < TAILLECHUNK_Z; z++)
            {
                chunk->entite[x][y][z] = 0;
            }
        }
    }
}

int chargerMap(char *cheminDossier, Map *map, double posX, double posZ, int distanceRendue)
{
    int i = 0, x, z;

    map->chunk = malloc(distanceRendue * distanceRendue * sizeof(Chunk));

    if(map->chunk != NULL)
    {
        for(x = (int)(posX / TAILLECHUNK_X) - (distanceRendue - 1) / 2; x <= (int)(posX / TAILLECHUNK_X) + (distanceRendue - 1) / 2; x++)
        {
            for(z = (int)(posZ / TAILLECHUNK_Z) - (distanceRendue - 1) / 2; z <= (int)(posZ / TAILLECHUNK_Z) + (distanceRendue - 1) / 2; z++)
            {
                chargerChunk(cheminDossier, &map->chunk[i], x, z);
                i++;
            }
        }
    }
    else
        printf("Erreur lors de l'allocation de mémoire de la map\n");

    return 1;
}

void dessinerMap(Map *map, GLuint texture, int distanceRendue)
{
    int i;

    for(i = 0; i < distanceRendue * distanceRendue; i++)
    {
        glPushMatrix();
        glTranslated(map->chunk[i].posX * TAILLECHUNK_X, 0, map->chunk[i].posZ * TAILLECHUNK_Z);
        dessinerChunk(&map->chunk[i], texture);
        glPopMatrix();
    }
}

int chargerChunk(char *cheminDossier, Chunk *chunk, int chunkX, int chunkZ)
{
    FILE *fichier = NULL;
    char cheminChunk[128] = {0};
    int x, y, z;

    sprintf(cheminChunk, "%s/chunk_%d.%d.mcrl", cheminDossier, chunkX, chunkZ);
    fichier = fopen(cheminChunk, "r");

    initChunk(chunk);

    if(fichier != NULL)
    {
        fscanf(fichier, "%d %d\n", &chunk->posX, &chunk->posZ);
        fscanf(fichier, "%d\n", &chunk->hauteurMax);
        for(y = 0; y < TAILLECHUNK_Y && y <= chunk->hauteurMax; y++)
        {
            for(x = 0; x < TAILLECHUNK_X; x++)
            {
                for(z = 0; z < TAILLECHUNK_Z; z++)
                {
                    fscanf(fichier, "%d ", &chunk->entite[x][y][z]);
                }
            }
        }
    }
    else
    {
        printf("création de fichier : %s\n", cheminChunk);
        creerChunk(cheminChunk, chunkX, chunkZ);
    }

    fclose(fichier);

    return 1;
}

void sauvegarderMap(char *cheminDossier, Map *map)
{
    int i;

    for(i = 0; i < CHUNK_MEM * CHUNK_MEM; i++)
    {
        sauvegarderChunk(cheminDossier, &map->chunk[i]);
    }
}

void sauvegarderChunk(char *cheminDossier, Chunk *chunk)
{
    if(chunk->modifie == 1)
    {
        FILE *fichier = NULL;
        char cheminChunk[128] = {0};
        int x, y, z;

        sprintf(cheminChunk, "%s/chunk_%d.%d.mcrl", cheminDossier, (int)chunk->posX, (int)chunk->posZ);
        fichier = fopen(cheminChunk, "w");

        if(fichier != NULL)
        {
            fprintf(fichier, "%d %d\n", chunk->posX, chunk->posZ);
            fprintf(fichier, "%d\n", chunk->hauteurMax);
            for(y = 0; y < TAILLECHUNK_Y; y++)
            {
                for(x = 0; x < TAILLECHUNK_X; x++)
                {
                    for(z = 0; z < TAILLECHUNK_Z; z++)
                    {
                        fprintf(fichier, "%d ", chunk->entite[x][y][z]);
                    }
                }
                fprintf(fichier, "\n");
            }
            fprintf(fichier, "\n");
        }
        else
            printf("Fichier de la map corrompu.\n");

        fclose(fichier);
    }
}

void libererChunk(Chunk *chunk)
{
    int x, y, z;

    for(y = 0; y < TAILLECHUNK_Y && y < chunk->hauteurMax; y++)
    {
        for(x = 0; x < TAILLECHUNK_X; x++)
        {
            for(z = 0; z < TAILLECHUNK_Z; z++)
            {
                chunk->entite[x][y][z] = 0;
            }
        }
    }
    chunk->posX = 0;
    chunk->posZ = 0;
}

void gererChunk(Map *map, char *cheminDossier, double posX, double posZ)
{
    int i, x, z;
    int chunkX, chunkZ;

    if((int)posX >= 0)
        chunkX = posX / TAILLECHUNK_X;
    else
        chunkX = posX / TAILLECHUNK_X - 1;

    if((int)posZ >= 0)
        chunkZ = posZ / TAILLECHUNK_Z;
    else
        chunkZ = posZ / TAILLECHUNK_Z - 1;

    for(i = 0; i < CHUNK_MEM * CHUNK_MEM; i++)
    {
        if(chunkX - ((CHUNK_MEM - 1) / 2) > map->chunk[i].posX || chunkX + ((CHUNK_MEM - 1) / 2) < map->chunk[i].posX || chunkZ - ((CHUNK_MEM - 1) / 2) > map->chunk[i].posZ || chunkZ + ((CHUNK_MEM - 1) / 2) < map->chunk[i].posZ)
        {
            sauvegarderChunk(cheminDossier, &map->chunk[i]);
            libererChunk(&map->chunk[i]);
            for(x = (int)chunkX - ((CHUNK_MEM - 1) / 2); x <= (int)chunkX + ((CHUNK_MEM - 1) / 2); x++)
            {
                for(z = (int)chunkZ - ((CHUNK_MEM - 1) / 2); z <= (int)chunkZ + ((CHUNK_MEM - 1) / 2); z++)
                {
                    if(retrouverChunk(map, x, z, NULL) == -1)
                    {
                        chargerChunk(cheminDossier, &map->chunk[i], x, z);
                    }
                }
            }
        }
    }
}

void creerChunk(char *cheminChunk, int chunkX, int chunkZ)
{
    int x, y, z;
    FILE *fichier = NULL;
    fichier = fopen(cheminChunk, "w+");

    if(fichier != NULL)
    {
        fprintf(fichier, "%d %d\n", chunkX, chunkZ);
        fprintf(fichier, "0\n");
        for(y = 0; y < TAILLECHUNK_Y; y++)
        {
            for(x = 0; x < TAILLECHUNK_X; x++)
            {
                for(z = 0; z < TAILLECHUNK_Z; z++)
                {
                    fprintf(fichier, "0 ");
                }
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\n");
    }
    else
    {
        printf("Impossible de créer le fichier : %s\n", cheminChunk);
    }

    fclose(fichier);
}