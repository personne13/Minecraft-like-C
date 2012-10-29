#include "constantes.h"
#include "map.h"
#include "input.h"
#include "jeu.h"
#include "bruits.h"

#define BUFFER_OFFSET(a) ((char*)NULL + (a))

extern Pave cube[NOMBRE_ENTITE];
extern float pos;

int chargerBlocs(char *chemin, Pave *bloc, int nombreBlocs)//Chargement des textures des blocs à l'aide du fichier "bloc.info"
{
    FILE *fichier = NULL;
    int i, j;
    double versionFichier = 0, versionActuelle = 0.02;

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
                for(j = 0; j < 6; j++)
                {
                    fscanf(fichier, "%f %f %f", &bloc[i].face[j].couleur.r, &bloc[i].face[j].couleur.v, &bloc[i].face[j].couleur.b);
                }
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

void dessinerChunk(Map *map, GLuint texture, int indiceChunk, Point *pos, Point *cible)
{
    static int x, y, z, i, indiceChunkCache = 0;
    static char facesAffichables[6] = {1, 1, 1, 1, 1, 1};
    static double distanceFace[4] = {0};
    static double moyenneDistances = 0;
    static double xCube = 0, yCube = 0, zCube = 0;
    static double faceX = 0, faceY = 0, faceZ = 0;

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor3ub(178, 178, 178);

    for(y = 0; y < TAILLECHUNK_Y && y < map->chunk[indiceChunk].hauteurMax; y++)
    {
        for(x = 0; x < TAILLECHUNK_X; x++)
        {
            for(z = 0; z < TAILLECHUNK_Z; z++)
            {
                if(map->chunk[indiceChunk].entite[x][y][z] != 0 && map->chunk[indiceChunk].entite[x][y][z] != 20 && map->chunk[indiceChunk].entite[x][y][z] != 18)//Affichage des blocs non-transparents
                {
                    xCube = 0.5 + map->chunk[indiceChunk].posX * TAILLECHUNK_X + x;
                    yCube = 0.5 + y;
                    zCube = 0.5 + map->chunk[indiceChunk].posZ * TAILLECHUNK_Z + z;

                    if((xCube - pos->x) * (xCube - pos->x) + (yCube - pos->y) * (yCube - pos->y) + (zCube - pos->z) * (zCube - pos->z) > (xCube - cible->x) * (xCube - cible->x) + (yCube - cible->y) * (yCube - cible->y) + (zCube - cible->z) * (zCube - cible->z))
                    {
                        if(pos->y >= yCube)
                            facesAffichables[4] = 0;
                        else
                            facesAffichables[5] = 0;

                        moyenneDistances = 0;

                        for(i = 0; i < 4; i++)
                        {
                            faceY = (cube[map->chunk[indiceChunk].entite[x][y][z]].face[i].bas1.y + cube[map->chunk[indiceChunk].entite[x][y][z]].face[i].haut1.y) / 2 + y;
                            faceX = (cube[map->chunk[indiceChunk].entite[x][y][z]].face[i].bas1.x + cube[map->chunk[indiceChunk].entite[x][y][z]].face[i].haut2.x) / 2 + x + map->chunk[indiceChunk].posX * TAILLECHUNK_X;
                            faceZ = (cube[map->chunk[indiceChunk].entite[x][y][z]].face[i].bas1.z + cube[map->chunk[indiceChunk].entite[x][y][z]].face[i].haut2.z) / 2 + z + map->chunk[indiceChunk].posZ * TAILLECHUNK_Z;

                            distanceFace[i] = (faceX - pos->x) * (faceX - pos->x) + (faceY - pos->y) * (faceY - pos->y) + (faceZ - pos->z) * (faceZ - pos->z);
                            moyenneDistances += distanceFace[i];
                        }

                        moyenneDistances /= 4;

                        for(i = 0; i < 4; i++)
                        {
                            if(distanceFace[i] > moyenneDistances)
                                facesAffichables[i] = 0;
                        }

                        glPushMatrix();
                        glTranslated(x, y, z);

                        if(z > 0)
                        {
                            if(map->chunk[indiceChunk].entite[x][y][z - 1] != 0 && map->chunk[indiceChunk].entite[x][y][z - 1] != 20 && map->chunk[indiceChunk].entite[x][y + 1][z] != 18)
                            {
                                facesAffichables[0] = 0;
                            }
                        }
                        else
                        {
                            if(retrouverChunk(map, map->chunk[indiceChunk].posX, map->chunk[indiceChunk].posZ - 1, &indiceChunkCache))
                            {
                                if(map->chunk[indiceChunkCache].entite[x][y][TAILLECHUNK_Z - 1] != 0 && map->chunk[indiceChunkCache].entite[x][y][TAILLECHUNK_Z - 1] != 20 && map->chunk[indiceChunkCache].entite[x][y][TAILLECHUNK_Z - 1] != 18)
                                {
                                    facesAffichables[0] = 0;
                                }
                            }
                        }
                        if(x > 0)
                        {
                            if(map->chunk[indiceChunk].entite[x - 1][y][z] != 0 && map->chunk[indiceChunk].entite[x - 1][y][z] != 20 && map->chunk[indiceChunk].entite[x][y + 1][z] != 18)
                            {
                                facesAffichables[1] = 0;
                            }
                        }
                        else
                        {
                            if(retrouverChunk(map, map->chunk[indiceChunk].posX - 1, map->chunk[indiceChunk].posZ, &indiceChunkCache))
                            {
                                if(map->chunk[indiceChunkCache].entite[TAILLECHUNK_X - 1][y][z] != 0 && map->chunk[indiceChunkCache].entite[TAILLECHUNK_X - 1][y][z] != 20 && map->chunk[indiceChunkCache].entite[TAILLECHUNK_X - 1][y][z] != 18)
                                {
                                    facesAffichables[1] = 0;
                                }
                            }
                        }
                        if(z + 1 < TAILLECHUNK_Z)
                        {
                            if(map->chunk[indiceChunk].entite[x][y][z + 1] != 0 && map->chunk[indiceChunk].entite[x][y][z + 1] != 20 && map->chunk[indiceChunk].entite[x][y + 1][z] != 18)
                            {
                                facesAffichables[2] = 0;
                            }
                        }
                        else
                        {
                            if(retrouverChunk(map, map->chunk[indiceChunk].posX, map->chunk[indiceChunk].posZ + 1, &indiceChunkCache))
                            {
                                if(map->chunk[indiceChunkCache].entite[x][y][0] != 0 && map->chunk[indiceChunkCache].entite[x][y][0] != 20 && map->chunk[indiceChunkCache].entite[x][y][0] != 18)
                                {
                                    facesAffichables[2] = 0;
                                }
                            }
                        }
                        if(x + 1 < TAILLECHUNK_X)
                        {
                            if(map->chunk[indiceChunk].entite[x + 1][y][z] != 0 && map->chunk[indiceChunk].entite[x + 1][y][z] != 20 && map->chunk[indiceChunk].entite[x][y + 1][z] != 18)
                            {
                                facesAffichables[3] = 0;
                            }
                        }
                        else
                        {
                            if(retrouverChunk(map, map->chunk[indiceChunk].posX + 1, map->chunk[indiceChunk].posZ, &indiceChunkCache))
                            {
                                if(map->chunk[indiceChunkCache].entite[0][y][z] != 0 && map->chunk[indiceChunkCache].entite[0][y][z] != 20 && map->chunk[indiceChunkCache].entite[0][y][z] != 18)
                                {
                                    facesAffichables[3] = 0;
                                }
                            }
                        }
                        if(y > 0)
                        {
                            if(map->chunk[indiceChunk].entite[x][y - 1][z] != 0 && map->chunk[indiceChunk].entite[x][y - 1][z] != 20 && map->chunk[indiceChunk].entite[x][y + 1][z] != 18)
                            {
                                facesAffichables[4] = 0;
                            }
                        }
                        if(y + 1 < TAILLECHUNK_Y)
                        {
                            if(map->chunk[indiceChunk].entite[x][y + 1][z] != 0 && map->chunk[indiceChunk].entite[x][y + 1][z] != 20 && map->chunk[indiceChunk].entite[x][y + 1][z] != 18)
                            {
                                facesAffichables[5] = 0;
                            }
                        }

                        //dessinerCube(map->chunk[indiceChunk].entite[x][y][z], facesAffichables);
                        dessinerCubeVBO(map->chunk[indiceChunk].entite[x][y][z], facesAffichables);

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

    for(y = 0; y < TAILLECHUNK_Y && y < map->chunk[indiceChunk].hauteurMax; y++)
    {
        for(x = 0; x < TAILLECHUNK_X; x++)
        {
            for(z = 0; z < TAILLECHUNK_Z; z++)
            {
                if(map->chunk[indiceChunk].entite[x][y][z] == 20 || map->chunk[indiceChunk].entite[x][y][z] == 18)//Affichage des blocs transparents (séparation par soucis du rendu)
                {
                    glPushMatrix();
                    glTranslated(x, y, z);

                    if(z > 0)
                    {
                        if(map->chunk[indiceChunk].entite[x][y][z - 1] != 0)
                        {
                            facesAffichables[0] = 0;
                        }
                    }
                    else
                    {
                        if(retrouverChunk(map, map->chunk[indiceChunk].posX, map->chunk[indiceChunk].posZ - 1, &indiceChunkCache))
                        {
                            if(map->chunk[indiceChunkCache].entite[x][y][TAILLECHUNK_Z - 1] != 0)
                            {
                                facesAffichables[0] = 0;
                            }
                        }
                    }
                    if(x > 0)
                    {
                        if(map->chunk[indiceChunk].entite[x - 1][y][z] != 0)
                        {
                            facesAffichables[1] = 0;
                        }
                    }
                    else
                    {
                        if(retrouverChunk(map, map->chunk[indiceChunk].posX - 1, map->chunk[indiceChunk].posZ, &indiceChunkCache))
                        {
                            if(map->chunk[indiceChunkCache].entite[TAILLECHUNK_X - 1][y][z] != 0)
                            {
                                facesAffichables[1] = 0;
                            }
                        }
                    }
                    if(z + 1 < TAILLECHUNK_Z)
                    {
                        if(map->chunk[indiceChunk].entite[x][y][z + 1] != 0)
                        {
                            facesAffichables[2] = 0;
                        }
                    }
                    else
                    {
                        if(retrouverChunk(map, map->chunk[indiceChunkCache].posX, map->chunk[indiceChunk].posZ + 1, &indiceChunkCache))
                        {
                            if(map->chunk[indiceChunk].entite[x][y][0] != 0)
                            {
                                facesAffichables[2] = 0;
                            }
                        }
                    }
                    if(x + 1 < TAILLECHUNK_X)
                    {
                        if(map->chunk[indiceChunk].entite[x + 1][y][z] != 0)
                        {
                            facesAffichables[3] = 0;
                        }
                    }
                    else
                    {
                        if(retrouverChunk(map, map->chunk[indiceChunkCache].posX + 1, map->chunk[indiceChunk].posZ, &indiceChunkCache))
                        {
                            if(map->chunk[indiceChunk].entite[0][y][z] != 0)
                            {
                                facesAffichables[3] = 0;
                            }
                        }
                    }
                    if(y > 0)
                    {
                        if(map->chunk[indiceChunk].entite[x][y - 1][z] != 0)
                        {
                            facesAffichables[4] = 0;
                        }
                    }
                    if(y + 1 < TAILLECHUNK_Y)
                    {
                        if(map->chunk[indiceChunk].entite[x][y + 1][z] != 0)
                        {
                            facesAffichables[5] = 0;
                        }
                    }

                    //dessinerCube(map->chunk[indiceChunk].entite[x][y][z], facesAffichables);
                    dessinerCubeVBO(map->chunk[indiceChunk].entite[x][y][z], facesAffichables);

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

void dessinerCubeVBO(int IDCube, char facesAffichables[6])
{
    int i;

    glBindBuffer(GL_ARRAY_BUFFER, cube[IDCube - 1].IDVBO);

    glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    glTexCoordPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(72 * sizeof(float)));
    glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(72 * sizeof(float) + 48 * sizeof(float)));


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    for(i = 0; i < 6; i++)
    {
        if(facesAffichables[i] == 1)
        {
            glDrawArrays(GL_QUADS, i * 4, 4);
        }
    }
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

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

void dessinerMap(Map *map, GLuint texture, int distanceRendue, Point *pos, Point *cible)
{
    int i;

    for(i = 0; i < distanceRendue * distanceRendue; i++)
    {
        glPushMatrix();
        glTranslated(map->chunk[i].posX * TAILLECHUNK_X, 0, map->chunk[i].posZ * TAILLECHUNK_Z);
        dessinerChunk(map, texture, i, pos, cible);
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
        fichier = fopen(cheminChunk, "w+");

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

Uint32 obtenirPixelSurface(SDL_Surface *surface, int x, int y)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

int obtenirGrisPixel(SDL_Surface *surface, Uint32 pixel)
{
    Uint8 gris;
    Uint8 a;
    SDL_GetRGBA(pixel, surface->format, &gris, &gris, &gris, &a);

    return (int)gris;
}

void creerChunk(char *cheminChunk, int chunkX, int chunkZ)
{
    SDL_Surface *heightMap = NULL;
    int x, y, z;
    int valeurGris = 0;
    Chunk nouveauChunk;

    initChunk(&nouveauChunk);

    heightMap = IMG_Load("map/testMap/heightMap.bmp");
    if(heightMap == NULL)
    {
        printf("HeightMap introuvable\n");
        exit(EXIT_FAILURE);
    }

    nouveauChunk.posX = chunkX;
    nouveauChunk.posZ = chunkZ;

    for(x = 0; x < TAILLECHUNK_X; x++)
    {
        for(z = 0; z < TAILLECHUNK_Z; z++)
        {
            if(chunkX >= 0 && chunkZ >= 0)
            {
                valeurGris = obtenirGrisPixel(heightMap, obtenirPixelSurface(heightMap, x + chunkX * TAILLECHUNK_X, z + chunkZ * TAILLECHUNK_Z));
            }
            if(valeurGris > nouveauChunk.hauteurMax)
            {
                nouveauChunk.hauteurMax = valeurGris;
            }
            for(y = 0; y < valeurGris; y++)
            {
                if(y + 5 < valeurGris)
                {
                    nouveauChunk.entite[x][y][z] = 1;
                }
                else if(y + 1 < valeurGris)
                {
                    nouveauChunk.entite[x][y][z] = 3;
                }
                else
                {
                    nouveauChunk.entite[x][y][z] = 2;
                }
            }
        }
    }

    nouveauChunk.modifie = 1;

    /*if(fichier != NULL)
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

    fclose(fichier);*/

    sauvegarderChunk("map/testMap", &nouveauChunk);

    SDL_FreeSurface(heightMap);
}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int opp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * opp;

    switch(opp)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *) p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            * (Uint32 *) p = pixel;
            break;
    }
}

Uint32 obtenirCouleur(double rouge, double vert, double bleu)
{
   return (((int) (rouge * 255)) << 16) + (((int) (vert * 255)) << 8) + (int) (bleu * 255);
}

int obtenirPixel(int x, int y)
{
    double valeur = bruit_coherent2D(x, y, 0.5);
    return obtenirCouleur(valeur, valeur, valeur);
}

int creerHeightMap(int x, int y, int hauteurMax, SDL_Surface **heightMap)
{
    int i, j;

    (*heightMap) = SDL_CreateRGBSurface(SDL_HWSURFACE, x, y, 32, 0, 0, 0, 0);

    initBruit2D(x + 1, y + 1, 18, 2);

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            definirPixel(*heightMap, i, j, obtenirPixel(i, j));
        }
    }
    destroyBruit2D();

    return 1;
}
