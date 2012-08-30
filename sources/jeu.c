#include "constantes.h"
#include "input.h"
#include "jeu.h"
#include "map.h"
#include "obj.h"
#include "sdlglutils.h"
#include "texte.h"
#include "options.h"

extern Input event;
Pave cube[NOMBRE_BLOCS];//Tableau pour stocker chaque cube du jeu
Item items[NOMBRE_ITEMS];
Texture texturesGui[6];//Les éléments de l'affichage 2D
GLuint textureTexte = 0;
GLuint textureItem = 0;
int largeurLettre[255] = {0};
Commandes controls;
Mob personnage;
double angle = 0, angleSkyBox = 0;
Pave SkyBox;
Pave mainPersonnage;
Map map;

void jouer()
{
    int continuer = 1;
    int tpsActuel = 0, tpsPrecedent = 0;//FPS
    int tps1 = 0, tps2 = 0;

    Point posObjet;//Point où se trouve l'objet (position du joueur)
    double ay = 0, ax = 0;
    Point posCamera;//Point où se trouve le point à regarder

    GLuint textureTerrain = 0;
    GLuint gui[3] = {0};//Tableau pour stocker chaque élément d'affichage (texture)
    GLuint IDtexturePersonnage = 0;

    int blocActuel = 0, blocInvSelectionne = -1, IDblocInvSelectionne = -1, quantiteSelectionnee = 0;
    Inventaire inv;
    int i;
    int modeDeJeu = 0;//survie
    int enJeu = 1;
    int plus = 0;
    int vision = 0;

    for(i = 0; i < 255; i++)
    {
        largeurLettre[i] = 16;
    }

    posObjet.y = 1.62;
    posObjet.x = 0;
    posObjet.z = 0;

    posCamera.x = 0;
    posCamera.y = 1.62;
    posCamera.z = 0;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(69,(double)FENETRE_LARG/FENETRE_HAUT,0.01,10000);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    chargerTexture(&textureTerrain, "textures/terrain.png");
    chargerTexture(&gui[0], "textures/gui/gui.png");
    chargerTexture(&gui[1], "textures/gui/allitems.png");
    chargerTexture(&gui[2], "textures/gui/inventory.png");
    chargerTexture(&textureTexte, "textures/font/default.png");
    chargerTexture(&IDtexturePersonnage, "textures/mob/char.png");
    chargerTexture(&textureItem, "textures/gui/items.png");

    chargerLargeurLettres("textures/font/default.properties", largeurLettre);

    attribuerTexGui(texturesGui, gui);

    chargerMap("map/testMap", &map, posObjet.x, posObjet.z, CHUNK_MEM);
    chargerBlocs("textures/blocs.info", cube, NOMBRE_ENTITE);//Fichier où se trouve les identifiants des textures des blocs
    chargerItems(items, "textures/items.info");

    attribuerCube(&SkyBox, 5000);

    for(i = 0; i < NOMBRE_BLOCS; i++)
    {
        attribuerCube(&cube[i], (double)1.0);//Définition des coordonnées des points des faces des blocs
    }

    for(i = 0; i < 36; i++)
    {
        inv.IDEntite[i] = -1;
        inv.quantite[i] = 25;
    }

    chargerCommandes(&controls, "utilitaires/options.txt");

    inv.quantite[5] = 1;
    inv.IDEntite[0] = 1;
    inv.IDEntite[1] = 2;
    inv.quantite[1] = 1;
    inv.IDEntite[2] = 41;
    inv.IDEntite[3] = 4;
    inv.IDEntite[4] = 5;
    inv.IDEntite[5] = 7;
    inv.IDEntite[6] = 322;
    inv.IDEntite[7] = 13;
    inv.IDEntite[8] = 14;
    inv.IDEntite[9] = 15;
    inv.IDEntite[10] = 16;
    inv.IDEntite[11] = 17;
    inv.IDEntite[12] = 18;
    inv.IDEntite[13] = 19;
    inv.IDEntite[14] = 20;
    inv.IDEntite[15] = 21;
    inv.IDEntite[16] = 22;
    inv.IDEntite[17] = 322;
    inv.IDEntite[18] = 24;
    inv.IDEntite[19] = 25;
    inv.IDEntite[20] = 35;
    inv.IDEntite[21] = 121;
    inv.IDEntite[22] = 41;
    inv.IDEntite[23] = 42;
    inv.IDEntite[24] = 43;
    inv.IDEntite[25] = 46;
    inv.IDEntite[26] = 47;
    inv.IDEntite[27] = 48;
    inv.IDEntite[28] = 49;
    inv.IDEntite[29] = 57;
    inv.IDEntite[30] = 58;
    inv.IDEntite[31] = 61;
    inv.IDEntite[32] = 73;
    inv.IDEntite[33] = 80;
    inv.IDEntite[34] = 98;
    inv.IDEntite[35] = 123;

    initialiserInput(&event);

    attribuerPersonnage(&personnage, IDtexturePersonnage);

    while(continuer)
    {
        updateEvents(&event);//Actualisation des évènements

        if(event.quitter == 1)
            continuer = 0;

        if(event.touche[SDLK_ESCAPE] == 1)
        {
            event.touche[SDLK_ESCAPE] = 0;

            if(enJeu == 0)
                enJeu = 1;
            else
                menu(textureTexte, gui, largeurLettre);

            sauvegarderCommandes(controls, "utilitaires/options.txt");
        }

        if(event.touche[SDLK_LALT] == 1 && event.touche[SDLK_F4] == 1)
        {
            continuer = 0;
        }

        if(enJeu)
        {
            if(verifierEvenement(controls.utiliser) == 1)
            {
                collision(posObjet, posCamera, &map, cube[blocActuel], inv, blocActuel, 1);//On pose un bloc
                event.souris[controls.utiliser] = 0;
                supprimerEvenement(controls.utiliser);
            }
            if(verifierEvenement(controls.attaquer) == 1)
            {
                collision(posObjet, posCamera, &map, cube[blocActuel], inv, blocActuel, 0);//On casse un bloc
                event.souris[controls.attaquer] = 0;
                supprimerEvenement(controls.attaquer);
            }

            if(event.souris[SDL_BUTTON_WHEELUP] == 1)
            {
                blocActuel++;
                if(blocActuel > 8)
                    blocActuel = 0;
            }
            if(event.souris[SDL_BUTTON_WHEELDOWN] == 1)
            {
                blocActuel--;
                if(blocActuel < 0)
                    blocActuel = 8;
            }
        }
        if(verifierEvenement(controls.inv) == 1)
        {
            if(enJeu == 1)
                enJeu = 0;
            else
                enJeu = 1;

            supprimerEvenement(controls.inv);
        }
        if(verifierEvenement(controls.avancer) == 1 || verifierEvenement(controls.reculer) == 1)
        {
            if(angle < -45 && plus == 0)
                plus = 1;
            if(angle > 45 && plus == 1)
                plus = 0;

            tps1 = SDL_GetTicks();

            if(plus && tps1 > tps2 + 1)
            {
                angle += 3;
                tps2 = tps1;
            }
            if(!plus && tps1 > tps2 + 1)
            {
                angle -= 3;
                tps2 = tps1;
            }
        }
        else
        {
            tps1 = SDL_GetTicks();
            if(angle > 0 && tps1 > tps2 + 1)
            {
                angle -= 3;
                tps2 = tps1;
            }
            if(angle < 0 && tps1 > tps2 + 1)
            {
                angle += 3;
                tps2 = tps1;
            }
        }

        if(event.touche[SDLK_F6] == 1)
        {
            printf("Sauvegarde\n");
            sauvegarderMap("map/testMap", &map);
            event.touche[SDLK_F6] = 0;
        }

        if(enJeu == 1)
        {
            if(event.posX != FENETRE_LARG / 2 || event.posY != FENETRE_HAUT / 2) //On ignore la position du curseur si il est au centre (recentrage)
            {
                ay -= (double)event.xrel * 0.4;
                ax += (double)event.yrel * 0.4;
                if(ax < 0.1)
                    ax = 0.1;
                if(ax > 179.9)
                    ax = 179.9;

                ay = modulo(ay, 360);
            }
        }

        if(enJeu == 0)
        {
            blocInvSelectionne = gererInventaire(&inv, modeDeJeu, &IDblocInvSelectionne, &quantiteSelectionnee);
        }

        tpsActuel = SDL_GetTicks();//FPS

        if(tpsActuel - tpsPrecedent > 15)
        {
            angleSkyBox += 0.1;
            if(enJeu == 1)
                deplacer(&map, &posObjet, &posCamera, ax, ay);
            Dessiner(&posCamera, &posObjet, ay, ax, &inv, textureTerrain, gui, textureTexte, blocActuel, modeDeJeu, enJeu, blocInvSelectionne, IDblocInvSelectionne, vision, quantiteSelectionnee);
            gererChunk(&map, "map/testMap", posObjet.x, posObjet.z);
            tpsPrecedent = tpsActuel;
        }
        else
            SDL_Delay(15 - (tpsActuel - tpsPrecedent));

        if((event.posX > FENETRE_LARG - 50 || event.posX < 50 || event.posY > FENETRE_HAUT - 50 || event.posY < 50) && enJeu == 1)//On recentre le curseur uniquement si il dépasse une certaine limite pouur gagner en performance
            SDL_WarpMouse(FENETRE_LARG / 2, FENETRE_HAUT / 2);

        event.xrel = 0;
        event.yrel = 0;
    }

    glDisable(GL_TEXTURE_2D);
}

void Dessiner(Point *direction, Point *position, double ay, double ax, Inventaire *inv, GLuint texture, GLuint gui[], GLuint textureTexte, int blocActuel, int modeDeJeu, int enJeu, int blocInvSelectionne, int IDblocInvSelectionne, int vision, int quantiteSelectionnee)
{
    int i;
    int tailleCase = 32;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(69,(double)FENETRE_LARG/FENETRE_HAUT,0.001,10000);//3D

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    regarder(position, direction);

    glPushMatrix();

    glTranslated(direction->x, 0, direction->z);
    glRotated(ay, 0, 1, 0);

    glBegin(GL_LINES);//Flèche représentant le personnage

    glColor3ub(255,0,0);

    glVertex3d(0,0,-1);
    glVertex3d(0,0,1);

    glVertex3d(0,0,-1);
    glVertex3d(0.5,0,0.5);

    glVertex3d(0,0,-1);
    glVertex3d(-0.5,0,0.5);

    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINES);//Les lignes du sol

    glColor3ub(255,255,255);


    for(i = 0; i < 101; i++)
    {
        glVertex3d(i * 2,0,0);
        glVertex3d(i * 2,0,200);

        glVertex3d(0,0,i * 2);
        glVertex3d(200,0,i * 2);
    }

    glEnd();

    glPushMatrix();
    glRotated(angleSkyBox, 1, 0, 0);
    glTranslated(-2500, -2500, -2500);
    dessinerSkyBox(&SkyBox);
    glPopMatrix();

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glColor3ub(255,255,255);

    glPushMatrix();
    glTranslated(2, 1, 2);
    dessinerPersonnage(personnage, angle, ay, ax);
    glPopMatrix();

    dessinerMap(&map, texture, CHUNK_MEM);

    dessinerGui(inv, gui, texture, tailleCase, blocActuel, modeDeJeu, enJeu, blocInvSelectionne, IDblocInvSelectionne, quantiteSelectionnee);

    glFlush();
    SDL_GL_SwapBuffers();
}

void dessinerGui(Inventaire *inv, GLuint gui[], GLuint texture, int tailleCase, int blocActuel, int modeDeJeu, int enJeu, int blocInvSelectionne, int IDblocInvSelectionne, int quantiteSelectionnee)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0,FENETRE_LARG,0,FENETRE_HAUT, -1, 10000);//2D

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,0.8f);

    glBindTexture(GL_TEXTURE_2D, gui[0]);//Texture pour l'inventaire

    if(enJeu == 1)
    {
        glPushMatrix();
        glTranslated(0, 0, -110);
        afficherTexture(texturesGui[3]);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(0, 0, -110);
    afficherTexture(texturesGui[0]);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 0, -109);
    texturesGui[1].posX = FENETRE_LARG / 2 - texturesGui[0].weight / 2 + blocActuel * 40 - 2;
    afficherTexture(texturesGui[1]);
    glPopMatrix();

    glDisable(GL_BLEND);

    dessinerMiniatures(inv, texture, tailleCase);

    if(enJeu == 0)
        afficherInventaire(inv, modeDeJeu, gui, texture, blocInvSelectionne, IDblocInvSelectionne, quantiteSelectionnee);

    glPushMatrix();
    glTranslated(0, 0, -120);
    dessinerMain(inv, blocActuel);
    glPopMatrix();
}

void deplacer(Map *map, Point *posObjet, Point *posCamera, double ax ,double ay)//A améliorer
{
    int quartile = 1;

    double sinX = sin(M_PI * ax / 180);
    double cosX = cos(M_PI * ax / 180);
    double sinY = sin(M_PI * ay / 180);
    double cosY = cos(M_PI * ay / 180);

    double vitesse = 0.155;
    Point posObjetTmp;
    int posChunkX = posObjet->x / TAILLECHUNK_X, posChunkZ = posObjet->z / TAILLECHUNK_Z;

    if(posChunkX < 0 || posChunkX >= CHUNK_MEM || posChunkZ < 0 || posChunkZ >= CHUNK_MEM)
    {
        posChunkX = 0;
        posChunkZ = 0;
    }

    if(verifierEvenement(controls.avancer) == 1 || verifierEvenement(controls.reculer) == 1)
    {
        vitesse -= 0.05;
    }
    if(verifierEvenement(controls.gauche) == 1 || verifierEvenement(controls.droite) == 1)
    {
        vitesse -= 0.05;
    }

    posObjetTmp = (*posObjet);

    determinerQuartile(&quartile, ay);

    if(verifierEvenement(controls.avancer) == 1)
    {
        posObjetTmp.z += cosY * vitesse;
        posObjetTmp.x += sinY * vitesse;
    }
    if(verifierEvenement(controls.reculer) == 1)
    {
        posObjetTmp.z -= cosY * vitesse;
        posObjetTmp.x -= sinY * vitesse;
    }
    if(verifierEvenement(controls.gauche) == 1)
    {
        posObjetTmp.z -= (cos(M_PI * (ay - 90) / 180)) * vitesse;
        posObjetTmp.x -= (sin(M_PI * (ay - 90) / 180)) * vitesse;
    }
    if(verifierEvenement(controls.droite) == 1)
    {
        posObjetTmp.z += (cos(M_PI * (ay - 90) / 180)) * vitesse;
        posObjetTmp.x += (sin(M_PI * (ay - 90) / 180)) * vitesse;
    }

    if(verifierEvenement(controls.sauter) == 1)
    {
        posObjetTmp.y += 0.2;
    }
    else if(verifierEvenement(controls.sneak) == 1)
    {
        posObjetTmp.y -= 0.2;
    }

    (*posObjet) = posObjetTmp;

    posCamera->y = posObjet->y + cosX;
    posCamera->x = posObjet->x + sinY * sinX;
    posCamera->z = posObjet->z + cosY * sinX;
}

double radians(double angle)//Degré vers radians
{
    return (M_PI * angle) / 180;
}

void determinerQuartile(int *quartile, double ay)
{
    if(ay >= 0 && ay <= 90)
    {
        *quartile = 2;
    }
    if(ay > 90 && ay <= 180)
    {
        *quartile = 3;
    }
    if(ay > 180 && ay < 270)
    {
        *quartile = 4;
    }
    if(ay >= 270 && ay < 360)
    {
        *quartile = 1;
    }
}

double modulo(double nombre1,double nombre2)//Modulo entre variables de type double
{
    if(nombre1 > 0)
    {
        while(nombre1 >= nombre2)
            nombre1 -= nombre2;
    }
    else if(nombre1 < 0)
    {
        while(nombre1 <= nombre2)
            nombre1 += nombre2;
    }
    return nombre1;
}

void regarder(Point *position, Point *direction)
{
    //gluLookAt(12, 3, 0, direction.x, direction.y, direction.z, 0, 1, 0);
    gluLookAt(position->x, position->y, position->z, direction->x, direction->y, direction->z, 0, 1, 0);
}

void tirer(Point A, Point B, Point *M)//Ancien test, à supprimer
{
    double k = 2000;

    M->x = k * (B.x - A.x) + A.x;
    M->z = k * (B.z - A.z) + A.z;
    M->y = k * (B.y - A.y) + A.y;
}

int collision(Point A, Point B, Map *map, Pave cible, Inventaire inv, int blocActuel, int placer)
{
    static int face = -1, touche = 0;
    double portee = 5;
    static int posX, posY, posZ;
    static int colChunkX = 0, colChunkZ = 0;
    static int chunkX = 0, chunkZ = 0;
    static int i = 0;
    static int x = 0, y = 0, z = 0, xCol = 0, yCol = 0, zCol = 0, faceCol;
    static int tabX, tabZ;
    double distance = 50, tmp;

    posX = (int)A.x;
    posY = (int)A.y;
    posZ = (int)A.z;

    for(x = posX - (int)portee; x < posX + (int)portee; x++)
    {
        for(y = posY - (int)portee; y < posY + (int)portee; y++)
        {
            for(z = posZ - (int)portee; z < posZ + (int)portee; z++)
            {
                if(x >= 0)
                {
                    chunkX = x / TAILLECHUNK_X;
                    tabX = x - TAILLECHUNK_X * chunkX;
                }
                else
                {
                    if(x % TAILLECHUNK_X != 0)
                        chunkX = x / TAILLECHUNK_X - 1;
                    else
                        chunkX = x / TAILLECHUNK_X;

                        tabX = x - TAILLECHUNK_X * chunkX;
                }
                if(z >= 0)
                {
                    chunkZ = z / TAILLECHUNK_Z;
                    tabZ = z - TAILLECHUNK_Z * chunkZ;
                }
                else
                {
                    if(z % TAILLECHUNK_Z != 0)
                        chunkZ = z / TAILLECHUNK_Z - 1;
                    else
                        chunkZ = z / TAILLECHUNK_Z;

                        tabZ = z - TAILLECHUNK_Z * chunkZ;
                }

                if(!retrouverChunk(map, chunkX, chunkZ, &i))
                    return 0;

                if(map->chunk[i].posX == chunkX && map->chunk[i].posZ == chunkZ)
                {
                    if(tabX >= 0 && tabZ >= 0 && y >= 0 && y < TAILLECHUNK_Y)
                    {
                        if(map->chunk[i].entite[tabX][y][tabZ] != 0)
                        {
                            face = -1;
                            redefinirPositionCube(&cible, 1, chunkX, chunkZ, tabX, y, tabZ);
                            face = determinerFaceCollision(A, B, cible, &tmp);
                            if(face != -1)
                            {
                                touche = 1;
                                if(distance > tmp)
                                {
                                    distance = tmp;
                                    faceCol = face;
                                    xCol = tabX;
                                    yCol = y;
                                    zCol = tabZ;
                                    colChunkX = chunkX;
                                    colChunkZ = chunkZ;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(touche == 1 && distance < (int)portee)
    {
        printf("pos : %d %d %d\n", posX, posY, posZ);
        printf("%d %d %d\n", xCol, yCol, zCol);
        if(placer)
        {
            if(inv.IDEntite[blocActuel] < 256)
            {
                placerCube(map, colChunkX, colChunkZ, faceCol, xCol, yCol, zCol, inv.IDEntite[blocActuel]);
            }
        }
        else
        {
            if(retrouverChunk(map, colChunkX, colChunkZ, &i))
                casserCube(&map->chunk[i], faceCol, xCol, yCol, zCol);
        }
    }

    return face;
}

void afficherPoint(Point point)
{
    glVertex3d(point.x, point.y, point.z);
}

int determinerFaceCollision(Point A, Point B, Pave cible, double *portee)
{
    int face = -1, i = 0, touche = 0;
    double tmp;
    double distance[6] = {50.0};
    Point intersection;

    for(i = 0; i < 6; i++)
    {
        distance[i] = -1;
        if(cible.face[i].bas1.x > cible.face[i].bas2.x)
        {
            tmp = cible.face[i].bas1.x;
            cible.face[i].bas1.x = cible.face[i].bas2.x;
            cible.face[i].bas2.x = tmp;
        }

        if(cible.face[i].bas1.z > cible.face[i].bas2.z)
        {
            tmp = cible.face[i].bas1.z;
            cible.face[i].bas1.z = cible.face[i].bas2.z;
            cible.face[i].bas2.z = tmp;
        }

        face = -1;
        if(cible.face[i].bas1.x - cible.face[i].bas2.x != 0)
            intersection.x = (-A.z + (A.z - B.z) / (A.x - B.x) * A.x + cible.face[i].bas1.z - (cible.face[i].bas1.z - cible.face[i].bas2.z) / (cible.face[i].bas1.x - cible.face[i].bas2.x) * cible.face[i].bas1.x) / ((A.z - B.z) / (A.x - B.x) - (cible.face[i].bas1.z - cible.face[i].bas2.z) / (cible.face[i].bas1.x - cible.face[i].bas2.x));
        else
            intersection.x = cible.face[i].bas1.x;

        intersection.z = (A.z - B.z) / (A.x - B.x) * intersection.x + A.z - (A.z - B.z) / (A.x - B.x) * A.x;
        intersection.y = (A.y - B.y) / (A.z - B.z) * intersection.z + A.y - (A.y - B.y) / (A.z - B.z) * A.z;

        if(cible.face[i].bas1.y == cible.face[i].haut1.y)
        {
            intersection.y = cible.face[i].bas1.y;
            intersection.x = (cible.face[i].bas1.y - A.y + (A.y - B.y) / (A.x - B.x) * A.x) / ((A.y - B.y) / (A.x - B.x));
            intersection.z = (cible.face[i].bas1.y - A.y + (A.y - B.y) / (A.z - B.z) * A.z) / ((A.y - B.y) / (A.z - B.z));
        }

        if(intersection.x >= cible.face[i].bas1.x && intersection.x <= cible.face[i].haut2.x)
        {
            if(intersection.y >= cible.face[i].bas1.y && intersection.y <= cible.face[i].haut1.y)
            {
                cible.face[i].bas1.z -= 0.0000000000001;
                cible.face[i].bas2.z += 0.0000000000001;
                if(intersection.z >= cible.face[i].bas1.z && intersection.z <= cible.face[i].bas2.z)
                {
                    face = i;
                    touche = 1;
                }
            }
        }

        if(face != -1)
        {
            distance[i] = sqrt((A.x - intersection.x)*(A.x - intersection.x) + (A.y - intersection.y)*(A.y - intersection.y) + (A.z - intersection.z)*(A.z - intersection.z));
        }

        if(distance[i] < sqrt((B.x - intersection.x)*(B.x - intersection.x) + (B.y - intersection.y)*(B.y - intersection.y) + (B.z - intersection.z)*(B.z - intersection.z)))
        {
            face = -1;
            distance[i] = 50.0;
        }
    }

    tmp = 0;

    if(touche == 1)
    {
        for(i = 0; i < 6; i++)
        {
            if((tmp > distance[i] && distance[i] > 0) || (tmp == 0 && distance[i] > 0))
            {
                tmp = distance[i];
                face = i;
            }
        }
    }

    (*portee) = tmp;//Distance entre la face touchée et le personnage

    return face;
}

void redefinirPositionCube(Pave *cube, int dimension, int chunkX, int chunkZ, int x, int y, int z)
{
    cube->face[0].bas1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[0].bas1.y = y;
    cube->face[0].bas1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[0].bas2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[0].bas2.y = y;
    cube->face[0].bas2.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[0].haut1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[0].haut1.y = dimension + y;
    cube->face[0].haut1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[0].haut2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[0].haut2.y = dimension + y;
    cube->face[0].haut2.z = z + TAILLECHUNK_Z * chunkZ;


    cube->face[1].bas1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[1].bas1.y = y;
    cube->face[1].bas1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[1].bas2.x = x + TAILLECHUNK_X * chunkX;
    cube->face[1].bas2.y = y;
    cube->face[1].bas2.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[1].haut1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[1].haut1.y = dimension + y;
    cube->face[1].haut1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[1].haut2.x = x + TAILLECHUNK_X * chunkX;
    cube->face[1].haut2.y = dimension + y;
    cube->face[1].haut2.z = dimension + z + TAILLECHUNK_Z * chunkZ;


    cube->face[2].bas1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[2].bas1.y = y;
    cube->face[2].bas1.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[2].bas2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[2].bas2.y = y;
    cube->face[2].bas2.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[2].haut1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[2].haut1.y = dimension + y;
    cube->face[2].haut1.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[2].haut2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[2].haut2.y = dimension + y;
    cube->face[2].haut2.z = dimension + z + TAILLECHUNK_Z * chunkZ;


    cube->face[3].bas1.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[3].bas1.y = y;
    cube->face[3].bas1.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[3].bas2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[3].bas2.y = y;
    cube->face[3].bas2.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[3].haut1.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[3].haut1.y = dimension + y;
    cube->face[3].haut1.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[3].haut2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[3].haut2.y = dimension + y;
    cube->face[3].haut2.z = z + TAILLECHUNK_Z * chunkZ;


    cube->face[4].bas1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[4].bas1.y = y;
    cube->face[4].bas1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[4].bas2.x = x + TAILLECHUNK_X * chunkX;
    cube->face[4].bas2.y = y;
    cube->face[4].bas2.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[4].haut1.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[4].haut1.y = y;
    cube->face[4].haut1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[4].haut2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[4].haut2.y = y;
    cube->face[4].haut2.z = dimension + z + TAILLECHUNK_Z * chunkZ;


    cube->face[5].bas1.x = x + TAILLECHUNK_X * chunkX;
    cube->face[5].bas1.y = dimension + y;
    cube->face[5].bas1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[5].bas2.x = x + TAILLECHUNK_X * chunkX;
    cube->face[5].bas2.y = dimension + y;
    cube->face[5].bas2.z = dimension + z + TAILLECHUNK_Z * chunkZ;

    cube->face[5].haut1.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[5].haut1.y = dimension + y;
    cube->face[5].haut1.z = z + TAILLECHUNK_Z * chunkZ;

    cube->face[5].haut2.x = dimension + x + TAILLECHUNK_X * chunkX;
    cube->face[5].haut2.y = dimension + y;
    cube->face[5].haut2.z = dimension + z + TAILLECHUNK_Z * chunkZ;
}

int placerCube(Map *map, int colChunkX, int colChunkZ, int face, int x, int y, int z, int bloc)
{
    int i = 0;

    if(!retrouverChunk(map, colChunkX, colChunkZ, &i))
    {
        return 0;
    }
    if(bloc > 0)
    {
        switch(face)
        {
            case 0:
                if(z - 1 >= 0 && map->chunk[i].entite[x][y][z - 1] == 0)
                {
                    map->chunk[i].entite[x][y][z - 1] = bloc;
                }
                else if(z == 0)
                {
                    if(!retrouverChunk(map, colChunkX, colChunkZ - 1, &i))
                        return 0;
                    if(map->chunk[i].entite[x][y][TAILLECHUNK_Z - 1] == 0)
                    {
                        map->chunk[i].entite[x][y][TAILLECHUNK_Z - 1] = bloc;
                        if(y >= map->chunk[i].hauteurMax)
                        {
                            map->chunk[i].hauteurMax = y + 1;
                        }
                    }
                }
                break;
            case 1:
                if(x - 1 >= 0 && map->chunk[i].entite[x - 1][y][z] == 0)
                    map->chunk[i].entite[x - 1][y][z] = bloc;
                else if(x == 0)
                {
                    if(!retrouverChunk(map, colChunkX - 1, colChunkZ, &i))
                        return 0;
                    if(map->chunk[i].entite[TAILLECHUNK_X - 1][y][z] == 0)
                    {
                        map->chunk[i].entite[TAILLECHUNK_X - 1][y][z] = bloc;
                        if(y >= map->chunk[i].hauteurMax)
                        {
                            map->chunk[i].hauteurMax = y + 1;
                        }
                    }
                }
                break;
            case 2:
                if(z + 1 < TAILLECHUNK_Z && map->chunk[i].entite[x][y][z + 1] == 0)
                    map->chunk[i].entite[x][y][z + 1] = bloc;
                else if(z + 1 == TAILLECHUNK_Z)
                {
                    if(!retrouverChunk(map, colChunkX, colChunkZ + 1, &i))
                        return 0;
                    if(map->chunk[i].entite[x][y][0] == 0)
                    {
                        map->chunk[i].entite[x][y][0] = bloc;
                        if(y >= map->chunk[i].hauteurMax)
                        {
                            map->chunk[i].hauteurMax = y + 1;
                        }
                    }
                }
                break;
            case 3:
                if(x + 1 < TAILLECHUNK_X && map->chunk[i].entite[x + 1][y][z] == 0)
                    map->chunk[i].entite[x + 1][y][z] = bloc;
                else if(x + 1 == TAILLECHUNK_X)
                {
                    if(!retrouverChunk(map, colChunkX + 1, colChunkZ, &i))
                    {
                        return 0;
                    }
                    if(map->chunk[i].entite[0][y][z] == 0)
                    {
                        map->chunk[i].entite[0][y][z] = bloc;
                        if(y >= map->chunk[i].hauteurMax)
                        {
                            map->chunk[i].hauteurMax = y + 1;
                        }
                    }
                }
                break;
            case 4:
                if(y - 1 >= 0 && map->chunk[i].entite[x][y - 1][z] == 0)
                    map->chunk[i].entite[x][y - 1][z] = bloc;
                break;
            case 5:
                if(y + 1 < TAILLECHUNK_Y && map->chunk[i].entite[x][y + 1][z] == 0)
                {
                    map->chunk[i].entite[x][y + 1][z] = bloc;
                    if(y + 2 >= map->chunk[i].hauteurMax)
                    {
                        map->chunk[i].hauteurMax = y + 2;
                    }
                }
                break;
        }
    }

    map->chunk[i].modifie = 1;

    return 1;
}

void casserCube(Chunk *terrain, int face, int x, int y, int z)
{
    terrain->entite[x][y][z] = 0;
    terrain->modifie = 1;
}

void dessinerMiniatures(Inventaire *inv, GLuint texture, int tailleCase)
{
    int j, coef = 20;
    Texte texteQuantite;

    texteQuantite.nbCara = 2;
    texteQuantite.chaine = malloc((texteQuantite.nbCara + 1) * sizeof(char));

    glBindTexture(GL_TEXTURE_2D, texture);

    for(j = 0; j < 9; j++)
    {
        if(inv->IDEntite[j] != 0)
        {
            glPushMatrix();


            if(inv->IDEntite[j] - 1 > -1 && inv->IDEntite[j] < 256)
            {
                glTranslated(FENETRE_LARG / 2 - texturesGui[0].weight / 2 + j * 40 + 7, texturesGui[0].height - 28, -100);
                glRotated(45, 0, 1, 0);
                glRotated(21, 0, 0, 1);
                glRotated(19.8, 1, 0, 0);
                afficherCubeMiniature(cube[inv->IDEntite[j] - 1], texture, coef);
            }
            else if(inv->IDEntite[j] > 256)
            {
                glTranslated(FENETRE_LARG / 2 - texturesGui[0].weight / 2 + j * 40 + 5, -FENETRE_HAUT + texturesGui[0].height - 1, -100);
                afficherItem(items, inv->IDEntite[j], textureItem);
            }


            glPopMatrix();

            if(inv->quantite[j] > 1)
            {
                sprintf(texteQuantite.chaine, "%d", inv->quantite[j]);
                glPushMatrix();
                glTranslated(FENETRE_LARG / 2 - texturesGui[0].posX + j * 40 - recupererLargeurChaine(texteQuantite, largeurLettre) + 75, -FENETRE_HAUT + texturesGui[0].height - 20, 0);
                afficherTexte(textureTexte, texteQuantite, largeurLettre, 1, 0, 0);
                glPopMatrix();
            }
        }
    }
    free(texteQuantite.chaine);
}

void afficherCubeMiniature(Pave cube, GLuint texture, int coef)
{
    int i;
    double posTexture[4] = {0.0};
    GLfloat transparent[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat vert[] = {(float)60/255, (float)179/255, (float)40/255};

    int xTex, yTex, IDbloc;

    glBindTexture(GL_TEXTURE_2D, texture);

    glEnable(GL_BLEND);
    glColor4fv(transparent);

    glBegin(GL_QUADS);

    for(i = 0; i < 6; i++)
    {
        IDbloc = cube.face[i].IdTexture;
        yTex = IDbloc / 16;
        xTex = IDbloc - (16 * yTex);

        posTexture[0] = (double)xTex/16;
        posTexture[1] = (double)(xTex + 1) / 16;
        posTexture[2] = (double)(16 - (yTex + 1)) / 16;
        posTexture[3] = (double)(16 - yTex) / 16;

        glColor3ub(42 * (i + 1),42 * (i + 1),42 * (i + 1));
        if(cube.ID == 18 || (cube.ID == 2 && i == 5))
            glColor3fv(vert);

        glTexCoord2d(posTexture[0], posTexture[2]);
        glVertex3d(cube.face[i].bas1.x * coef, cube.face[i].bas1.y * coef, cube.face[i].bas1.z * coef);
        glTexCoord2d(posTexture[1], posTexture[2]);
        glVertex3d(cube.face[i].bas2.x * coef, cube.face[i].bas2.y * coef, cube.face[i].bas2.z * coef);
        glTexCoord2d(posTexture[1], posTexture[3]);
        glVertex3d(cube.face[i].haut2.x * coef, cube.face[i].haut2.y * coef, cube.face[i].haut2.z * coef);
        glTexCoord2d(posTexture[0], posTexture[3]);
        glVertex3d(cube.face[i].haut1.x * coef, cube.face[i].haut1.y * coef, cube.face[i].haut1.z * coef);
    }

    glEnd();

    glDisable(GL_BLEND);
}

void afficherInventaire(Inventaire *inv, int modeDeJeu, GLuint gui[], GLuint textureTerrain, int blocInvSelectionne, int IDblocInvSelectionne, int quantiteSelectionnee)
{
    GLfloat transparent[] = {0.9f, 0.9f, 0.9f, 0.4f};
    GLfloat blanc[] = {1.0f, 1.0f, 1.0f, 1.0f};
    Texte texteQuantite;

    texteQuantite.nbCara = 2;
    texteQuantite.chaine = malloc((texteQuantite.nbCara + 1) * sizeof(char));

    int posX, posY;

    glEnable(GL_BLEND);

    if(modeDeJeu == 1)
    {
        glPushMatrix();
        glColor4fv(blanc);
        glTranslated(0, 0, -109);
        afficherTexture(texturesGui[4]);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glColor4fv(blanc);
        glTranslated(0, 0, -130);
        afficherTexture(texturesGui[2]);
        glPopMatrix();

        miniaturesInventaire(inv, modeDeJeu, textureTerrain);

        if(blocInvSelectionne != -1)
        {
            glPushMatrix();
            glTranslated(0, 0, -70);
            glColor4fv(transparent);
            posY = blocInvSelectionne / 9;
            posX = blocInvSelectionne - (posY * 9);

            if(posY > 0)
            {
                texturesGui[5].posX = texturesGui[2].posX + 16 + posX * 36;
                texturesGui[5].posY = texturesGui[2].posY + 167 + (posY - 1) * 36;
            }
            else
            {
                texturesGui[5].posX = texturesGui[2].posX + 16 + posX * 36;
                texturesGui[5].posY = texturesGui[2].posY + 284 + posY * 36;
            }
            afficherTexture(texturesGui[5]);
            glColor4fv(blanc);
            glPopMatrix();
        }

        if(IDblocInvSelectionne != -1)
        {
            glPushMatrix();
            if(IDblocInvSelectionne < 256)
            {
                glTranslated(event.posX - 15, FENETRE_HAUT - event.posY - 12, -60);
                glRotated(45, 0, 1, 0);
                glRotated(21, 0, 0, 1);
                glRotated(19.8, 1, 0, 0);
                afficherCubeMiniature(cube[IDblocInvSelectionne - 1], textureTerrain, 20);
            }
            else
            {
                glTranslated(event.posX - 15, -event.posY + 16, -60);
                afficherItem(items, IDblocInvSelectionne, textureItem);
            }
            glPopMatrix();

            if(quantiteSelectionnee > 1)
            {
                glPushMatrix();
                sprintf(texteQuantite.chaine, "%d", quantiteSelectionnee);
                glTranslated(event.posX + 15 - recupererLargeurChaine(texteQuantite, largeurLettre), -event.posY - 5, -30);
                afficherTexte(textureTexte, texteQuantite, largeurLettre, 1, 0, 0);
                glPopMatrix();
            }
        }
    }

    glDisable(GL_BLEND);
}

void miniaturesInventaire(Inventaire *inv, int modeDeJeu, GLuint textureTerrain)
{
    double posX, posY;
    int i;
    Texte texteQuantite;

    texteQuantite.nbCara = 2;
    texteQuantite.chaine = malloc((texteQuantite.nbCara + 1) * sizeof(char));

    if(modeDeJeu == 1)
    {
    }
    else
    {
        for(i = 0; i < 36; i++)
        {
            if(inv->IDEntite[i] != 0)
            {
                if(i < 9)
                {
                    posY = FENETRE_HAUT - texturesGui[2].posY - 310;
                    posX = FENETRE_LARG / 2 - 176 + i * 36 + 18;
                }
                else if(i < 18)
                {
                    posY = FENETRE_HAUT - texturesGui[2].posY - 194;
                    posX = FENETRE_LARG / 2 + 176 - (17 - i) * 36 - 46;
                }
                else if(i < 27)
                {
                    posY = FENETRE_HAUT - texturesGui[2].posY - 230;
                    posX = FENETRE_LARG / 2 + 176 - (26 - i) * 36 - 46;
                }
                else if(i < 36)
                {
                    posY = FENETRE_HAUT - texturesGui[2].posY - 266;
                    posX = FENETRE_LARG / 2 + 176 - (35 - i) * 36 - 46;
                }

                glPushMatrix();

                if(inv->IDEntite[i] - 1 > -1 && inv->IDEntite[i] < 256)
                {
                    glTranslated(posX, posY, -102);
                    glRotated(45, 0, 1, 0);
                    glRotated(21, 0, 0, 1);
                    glRotated(19.8, 1, 0, 0);

                    afficherCubeMiniature(cube[inv->IDEntite[i] - 1], textureTerrain, 20);
                }
                else if(inv->IDEntite[i] > 256)
                {
                    glTranslated(posX - 2, -FENETRE_HAUT + posY + 26, -100);
                    afficherItem(items, inv->IDEntite[i], textureItem);
                }

                glPopMatrix();

                if(inv->quantite[i] > 1)
                {
                    glPushMatrix();
                    sprintf(texteQuantite.chaine, "%d", inv->quantite[i]);
                    glTranslated(posX + 30 - recupererLargeurChaine(texteQuantite, largeurLettre), posY - FENETRE_HAUT + 7, -80);
                    afficherTexte(textureTexte, texteQuantite, largeurLettre, 1, 0, 0);
                    glPopMatrix();
                }
            }
        }
    }

    free(texteQuantite.chaine);
}

int gererInventaire(Inventaire *inv, int modeDeJeu, int *IDblocInvSelectionne, int *quantiteSelectionnee)
{
    int xCurseur = -1, yCurseur = -1;
    int tailleCase = 36;
    int blocSelectionne = -1;
    int tmp;

    if(modeDeJeu == 0)
    {
        if(event.posX >= texturesGui[2].posX + 14 && event.posX <= texturesGui[2].posX + texturesGui[2].weight - 17)
            xCurseur = (event.posX - (texturesGui[2].posX + 12)) / tailleCase;

        if(event.posY >= texturesGui[2].posY + 165 && event.posY <= texturesGui[2].posY + 272)//blocs de l'inventaire non-accessibles
            yCurseur = (event.posY - (texturesGui[2].posY + 165)) / tailleCase;

        if(event.posY >= texturesGui[2].posY + 282 && event.posY <= texturesGui[2].posY + 317)//blocs de l'inventaire accessibles (rangée du bas)
            yCurseur = 3;

        if(xCurseur != -1 && yCurseur != -1)
        {
            if(yCurseur < 3)
                blocSelectionne = xCurseur + (yCurseur + 1) * 9;
            else
                blocSelectionne = xCurseur;
        }
        if(event.souris[SDL_BUTTON_LEFT] == 1 && blocSelectionne != -1)
        {
            if(inv->IDEntite[blocSelectionne] != (*IDblocInvSelectionne))
            {
                tmp = inv->IDEntite[blocSelectionne];
                inv->IDEntite[blocSelectionne] = (*IDblocInvSelectionne);
                (*IDblocInvSelectionne) = tmp;
                tmp = (*quantiteSelectionnee);
                (*quantiteSelectionnee) = inv->quantite[blocSelectionne];
                inv->quantite[blocSelectionne] = tmp;
            }
            else
            {
                tmp = (inv->quantite[blocSelectionne] + (*quantiteSelectionnee));
                if(tmp > 64)
                {
                    (*quantiteSelectionnee) = tmp - 64;
                    tmp = 64;
                    inv->quantite[blocSelectionne] = tmp;
                }
                else
                {
                    (*quantiteSelectionnee) = 0;
                    (*IDblocInvSelectionne) = -1;
                    inv->quantite[blocSelectionne] = tmp;
                }

            }
            event.souris[SDL_BUTTON_LEFT] = 0;
        }
        if(event.souris[SDL_BUTTON_RIGHT] == 1 && blocSelectionne != -1)
        {
            if((*IDblocInvSelectionne) != -1)
            {
                if(inv->IDEntite[blocSelectionne] == (*IDblocInvSelectionne))
                {
                    if(inv->quantite[blocSelectionne] < 64)
                    {
                        inv->quantite[blocSelectionne]++;
                        (*quantiteSelectionnee)--;
                        if((*quantiteSelectionnee) < 1)
                        {
                            (*quantiteSelectionnee) = 0;
                            (*IDblocInvSelectionne) = -1;
                        }
                    }
                }

                else if(inv->IDEntite[blocSelectionne] < 1)
                {
                    inv->IDEntite[blocSelectionne] = (*IDblocInvSelectionne);
                    inv->quantite[blocSelectionne]++;
                    (*quantiteSelectionnee)--;
                }

                else if(inv->IDEntite[blocSelectionne] != (*IDblocInvSelectionne))
                {
                    tmp = inv->IDEntite[blocSelectionne];
                    inv->IDEntite[blocSelectionne] = (*IDblocInvSelectionne);
                    (*IDblocInvSelectionne) = tmp;
                    tmp = (*quantiteSelectionnee);
                    (*quantiteSelectionnee) = inv->quantite[blocSelectionne];
                    inv->quantite[blocSelectionne] = tmp;
                }
            }
            else
            {
                if(inv->IDEntite[blocSelectionne] > 0)
                {
                    (*quantiteSelectionnee) = inv->quantite[blocSelectionne];
                    inv->quantite[blocSelectionne] = inv->quantite[blocSelectionne] / 2;
                    (*quantiteSelectionnee) -= inv->quantite[blocSelectionne];
                    if((*quantiteSelectionnee) > 0)
                        (*IDblocInvSelectionne) = inv->IDEntite[blocSelectionne];

                    if(inv->quantite[blocSelectionne] < 1)
                    {
                        inv->IDEntite[blocSelectionne] = -1;
                    }
                }
            }
            event.souris[SDL_BUTTON_RIGHT] = 0;
        }
    }

    return blocSelectionne;
}

void afficherTexture(Texture texture)
{
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture.IDtex);

    glBegin(GL_QUADS);
    glTexCoord2d((double)texture.posTexX / texture.wMax, (double)(texture.hMax - texture.posTexY) / texture.hMax);
    glVertex2d(texture.posX, FENETRE_HAUT - texture.posY);
    glTexCoord2d((double)(texture.posTexX + texture.weight) / texture.wMax, (double)(texture.hMax - texture.posTexY) / texture.hMax);
    glVertex2d(texture.posX + texture.weight, FENETRE_HAUT - texture.posY);
    glTexCoord2d((double)(texture.posTexX + texture.weight) / texture.wMax, (double)(texture.hMax - (texture.posTexY + texture.height)) / texture.hMax);
    glVertex2d(texture.posX + texture.weight, (FENETRE_HAUT - texture.posY) - texture.height);
    glTexCoord2d((double)(texture.posTexX) / texture.wMax, (double)(texture.hMax - (texture.posTexY + texture.height)) / texture.hMax);
    glVertex2d(texture.posX, (FENETRE_HAUT - texture.posY) - texture.height);
    glEnd();

    glDisable(GL_BLEND);
}

void attribuerTexGui(Texture texturesGui[], GLuint gui[])
{
    texturesGui[0].IDtex = gui[0];//Image de l'inventaire miniature (en bas)
    texturesGui[0].posTexX = 1;
    texturesGui[0].posTexY = 1;
    texturesGui[0].height = 42;
    texturesGui[0].weight = 362;
    texturesGui[0].wMax = 512;
    texturesGui[0].hMax = 512;
    texturesGui[0].posX = FENETRE_LARG / 2 - texturesGui[0].weight / 2;
    texturesGui[0].posY = FENETRE_HAUT - texturesGui[0].height - 2;

    texturesGui[1].IDtex = gui[0];//Carré de sélection
    texturesGui[1].posTexX = 1;
    texturesGui[1].posTexY = 45;
    texturesGui[1].height = 46;
    texturesGui[1].weight = 46;
    texturesGui[1].wMax = 512;
    texturesGui[1].hMax = 512;
    texturesGui[1].posX = FENETRE_LARG / 2 - texturesGui[0].weight / 2 - 2;
    texturesGui[1].posY = FENETRE_HAUT - texturesGui[1].height;

    texturesGui[2].IDtex = gui[2];//Image de l'inventaire (survie)
    texturesGui[2].posTexX = 0;
    texturesGui[2].posTexY = 0;
    texturesGui[2].height = 332;
    texturesGui[2].weight = 352;
    texturesGui[2].wMax = 512;
    texturesGui[2].hMax = 512;
    texturesGui[2].posX = FENETRE_LARG / 2 - texturesGui[2].weight / 2;
    texturesGui[2].posY = FENETRE_HAUT / 2 - texturesGui[2].height / 2;

    texturesGui[3].IDtex = gui[0];//Croix du milieu de la fenêtre
    texturesGui[3].posTexX = 484;
    texturesGui[3].posTexY = 4;
    texturesGui[3].height = 22;
    texturesGui[3].weight = 22;
    texturesGui[3].wMax = 512;
    texturesGui[3].hMax = 512;
    texturesGui[3].posX = FENETRE_LARG / 2 - texturesGui[3].weight / 2;
    texturesGui[3].posY = FENETRE_HAUT / 2 - texturesGui[3].height / 2;

    texturesGui[4].IDtex = gui[1];//Image de l'inventaire (créatif)
    texturesGui[4].posTexX = 0;
    texturesGui[4].posTexY = 0;
    texturesGui[4].height = 416;
    texturesGui[4].weight = 352;
    texturesGui[4].wMax = 512;
    texturesGui[4].hMax = 512;
    texturesGui[4].posX = FENETRE_LARG / 2 - texturesGui[4].weight / 2;
    texturesGui[4].posY = FENETRE_HAUT / 2 - texturesGui[4].height / 2;

    texturesGui[5].IDtex = gui[0];//Carré de sélection dans l'inventaire
    texturesGui[5].posTexX = 0;
    texturesGui[5].posTexY = 292;
    texturesGui[5].height = 34;
    texturesGui[5].weight = 34;
    texturesGui[5].wMax = 512;
    texturesGui[5].hMax = 512;
}

void menu(GLuint texTexte, GLuint gui[], int largeurLettre[255])
{
    int tpsActuel = 0, tpsPrecedent = 0;
    int continuer = 1, i, posX = 0, posY = 0;
    int menuActuel = 1;
    int saisieTouche = -1;
    int touche = 0;
    char c = 0;
    Bouton boutonsPrincipaux[5];
    Bouton boutonControles[14];
    Bouton boutonOptions[10];
    Texte fonctionBoutonsControles[13];

    for(i = 0; i < 5; i++)
    {
        attribuerTexBouton(&boutonsPrincipaux[i], gui);
    }
    for(i = 0; i < 10; i++)
    {
        attribuerTexBouton(&boutonOptions[i], gui);
    }
    for(i = 0; i < 14; i++)
    {
        attribuerTexBouton(&boutonControles[i], gui);
    }

    recupererCoordonneesBoutons("utilitaires/boutonsPrincipaux.txt", boutonsPrincipaux);
    recupererCoordonneesBoutons("utilitaires/boutonsOptions.txt", boutonOptions);
    recupererCoordonneesBoutons("utilitaires/boutonsControles.txt", boutonControles);

    for(i = 0; i < 13; i++)
    {
        fonctionBoutonsControles[i].nbCara = boutonControles[i].texte.nbCara;
        fonctionBoutonsControles[i].chaine = malloc((fonctionBoutonsControles[i].nbCara + 1) * sizeof(char));
        if(fonctionBoutonsControles[i].chaine == NULL)
        {
            printf("Impossible d'allouer de la mémoire\n");
            exit(EXIT_FAILURE);
        }
        sprintf(fonctionBoutonsControles[i].chaine, "%s", boutonControles[i].texte.chaine);
        free(boutonControles[i].texte.chaine);
        boutonControles[i].texte.nbCara = 0;
    }

    attribuerNomBoutonControle(&boutonControles[0].texte, controls.attaquer);
    attribuerNomBoutonControle(&boutonControles[1].texte, controls.utiliser);
    attribuerNomBoutonControle(&boutonControles[2].texte, controls.avancer);
    attribuerNomBoutonControle(&boutonControles[3].texte, controls.gauche);
    attribuerNomBoutonControle(&boutonControles[4].texte, controls.reculer);
    attribuerNomBoutonControle(&boutonControles[5].texte, controls.droite);
    attribuerNomBoutonControle(&boutonControles[6].texte, controls.sauter);
    attribuerNomBoutonControle(&boutonControles[7].texte, controls.sneak);
    attribuerNomBoutonControle(&boutonControles[8].texte, controls.drop);
    attribuerNomBoutonControle(&boutonControles[9].texte, controls.inv);
    attribuerNomBoutonControle(&boutonControles[10].texte, controls.chat);
    attribuerNomBoutonControle(&boutonControles[11].texte, controls.listeJoueurs);
    attribuerNomBoutonControle(&boutonControles[12].texte, controls.prendreBloc);

    while(continuer)
    {
        updateEvents(&event);

        if(event.touche[SDLK_ESCAPE] == 1)
        {
            continuer = 0;
            event.touche[SDLK_ESCAPE] = 0;
        }
        if(event.touche[SDLK_LALT] == 1 && event.touche[SDLK_F4] == 1)
        {
            exit(EXIT_SUCCESS);
        }
        if(event.quitter == 1)
        {
            exit(EXIT_SUCCESS);
        }
        if(menuActuel == 1)
        {
            for(i = 0; i < 5; i++)
            {
                collisionBouton(&boutonsPrincipaux[i]);
            }
        }
        if(menuActuel == 2)
        {
            for(i = 0; i < 10; i++)
            {
                collisionBouton(&boutonOptions[i]);
            }
        }
        if(menuActuel == 3)
        {
            for(i = 0; i < 14; i++)
            {
                collisionBouton(&boutonControles[i]);
            }
        }
        if(event.souris[SDL_BUTTON_LEFT] == 1)
        {
            if(saisieTouche == -1)
            {
                if(boutonsPrincipaux[0].selectionne == 1)
                    continuer = 0;
                if(boutonsPrincipaux[4].selectionne == 1)
                    continuer = 0;
                if(boutonsPrincipaux[3].selectionne == 1)
                {
                    menuActuel = 2;
                    boutonsPrincipaux[3].selectionne = 0;
                }
                if(boutonOptions[7].selectionne == 1)
                {
                    menuActuel = 3;
                    boutonOptions[7].selectionne = 0;
                }
                if(boutonOptions[9].selectionne == 1)
                {
                    menuActuel = 1;
                    boutonOptions[9].selectionne = 0;
                }
                if(boutonControles[13].selectionne == 1)
                {
                    menuActuel = 2;
                    boutonControles[13].selectionne = 0;
                }

                for(i = 0; i < 13; i++)
                {
                    if(boutonControles[i].selectionne == 1 && event.souris[SDL_BUTTON_LEFT] == 1)
                    {
                        boutonControles[i].texte.nbCara = 7;
                        boutonControles[i].texte.chaine = realloc(boutonControles[i].texte.chaine, (boutonControles[i].texte.nbCara + 1) * sizeof(char));
                        if(boutonControles[i].texte.chaine == NULL)
                        {
                            printf("Impossible d'allouer de la mémoire\n");
                            exit(EXIT_FAILURE);
                        }
                        sprintf(boutonControles[i].texte.chaine, "> ??? <");
                        saisieTouche = i;
                        initialiserInput(&event);
                    }
                }
                event.souris[SDL_BUTTON_LEFT] = 0;
            }
        }

        if(saisieTouche != -1)
        {
            c = eventCommande(&touche);

            if(c != 0)
            {
                c = toupper(c);
                free(boutonControles[saisieTouche].texte.chaine);

                switch(saisieTouche)
                {
                    case 0:
                        controls.attaquer = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.attaquer);
                        break;
                    case 1:
                        controls.utiliser = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.utiliser);
                        break;
                    case 2:
                        controls.avancer = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.avancer);
                        break;
                    case 3:
                        controls.gauche = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.gauche);
                        break;
                    case 4:
                        controls.reculer = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.reculer);
                        break;
                    case 5:
                        controls.droite = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.droite);
                        break;
                    case 6:
                        controls.sauter = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.sauter);
                        break;
                    case 7:
                        controls.sneak = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.sneak);
                        break;
                    case 8:
                        controls.drop = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.drop);
                        break;
                    case 9:
                        controls.inv = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.inv);
                        break;
                    case 10:
                        controls.chat = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.chat);
                        break;
                    case 11:
                        controls.listeJoueurs = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.listeJoueurs);
                        break;
                    case 12:
                        controls.prendreBloc = touche;
                        attribuerNomBoutonControle(&boutonControles[saisieTouche].texte, controls.prendreBloc);
                        break;
                }
                c = 0;
                touche = 0;
                saisieTouche = -1;
            }
        }

        tpsActuel = SDL_GetTicks();//FPS

        if(tpsActuel - tpsPrecedent > 20)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0,FENETRE_LARG,0,FENETRE_HAUT, -1, 10000);//2D
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            if(menuActuel == 1)
            {
                for(i = 0; i < 5; i++)
                {
                    glPushMatrix();
                    glTranslated(0, 0, -100);
                    afficherBouton(boutonsPrincipaux[i], texTexte);
                    glPopMatrix();
                }
            }
            if(menuActuel == 2)
            {
                for(i = 0; i < 10; i++)
                {
                    glPushMatrix();
                    glTranslated(0, 0, -100);
                    afficherBouton(boutonOptions[i], texTexte);
                    glPopMatrix();
                }
            }
            if(menuActuel == 3)
            {
                for(i = 0; i < 14; i++)
                {
                    glPushMatrix();
                    glTranslated(0, 0, -100);
                    afficherBouton(boutonControles[i], texTexte);
                    if(i < 13)
                    {
                        posX = boutonControles[i].posX + boutonControles[i].weight + 10;
                        posY = boutonControles[i].posY + 10;
                        afficherTexte(texTexte, fonctionBoutonsControles[i], largeurLettre, 1, posX, posY);
                    }
                    glPopMatrix();
                }
            }

            glFlush();
            SDL_GL_SwapBuffers();
            tpsPrecedent = tpsActuel;
        }
        else
            SDL_Delay(20 - (tpsActuel - tpsPrecedent));
    }

    for(i = 0; i < 5; i++)
        free(boutonsPrincipaux[i].texte.chaine);

    for(i = 0; i < 10; i++)
        free(boutonOptions[i].texte.chaine);

    for(i = 0; i < 14; i++)
        free(boutonControles[i].texte.chaine);
}

int recupererCoordonneesBoutons(char *cheminFichier, Bouton *bouton)
{
    FILE *fichier = NULL;
    int nombreBoutons = 0, i, j, h;
    int variable = 0;
    char c = 0;
    char buffer[128] = {0};

    fichier = fopen(cheminFichier, "r");

    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", cheminFichier);
        return 0;
    }

    fscanf(fichier, "nombreBoutons = %d\n", &nombreBoutons);

    for(i = 0; i < nombreBoutons; i++)
    {
        fscanf(fichier, "boutons%d.weight = %d\n", &j, &variable);
        bouton[j].weight = variable;

        fscanf(fichier, "boutons%d.height = %d\n", &j, &variable);
        bouton[j].height = variable;

        fscanf(fichier, "boutons%d.posX = %d\n", &j, &variable);
        bouton[j].posX = variable;

        fscanf(fichier, "boutons%d.posY = %d\n", &j, &variable);
        bouton[j].posY = variable;

        fscanf(fichier, "boutons%d.texte = ", &j);

        do
        {
            fscanf(fichier, "%c", &c);
            if(c != '\n')
                buffer[bouton[j].texte.nbCara] = c;

            bouton[j].texte.nbCara++;
        }while(c != '\n');
        fscanf(fichier, "%c", &c);

        bouton[j].texte.nbCara--;

        bouton[j].texte.chaine = malloc((bouton[j].texte.nbCara + 1) * sizeof(char));
        if(bouton[j].texte.chaine == NULL)
        {
            printf("Erreur d'allocation de mémoire\n");
            exit(EXIT_FAILURE);
        }
        sprintf(bouton[j].texte.chaine, "%s", buffer);

        for(h = 0; h < 128; h++)
            buffer[h] = 0;
    }

    return 1;
}

void attribuerTexBouton(Bouton *bouton, GLuint gui[])
{
    bouton->selectionne = 0;
    bouton->IDtex = gui[0];
    bouton->wMax = 512;
    bouton->hMax = 512;
    bouton->posTex1DebX = 0;
    bouton->posTex1DebY = 132;
    bouton->posTex1FinX = 399;
    bouton->posTex1FinY = 171;
    bouton->posTex2DebX = 0;
    bouton->posTex2DebY = 172;
    bouton->posTex2FinX = 399;
    bouton->posTex2FinY = 211;
    bouton->texte.nbCara = 0;
    bouton->texte.chaine = NULL;
}

void afficherBouton(Bouton bt, GLuint texTexte)
{
    int posTexteX, posTexteY;
    glBindTexture(GL_TEXTURE_2D, bt.IDtex);

    glBegin(GL_QUADS);
    if(bt.selectionne == 1)
    {
        glTexCoord2d((double)bt.posTex2DebX / bt.wMax, (double)(bt.hMax - bt.posTex2DebY) / bt.hMax);
        glVertex2d(bt.posX, FENETRE_HAUT - bt.posY);
        glTexCoord2d((double)bt.posTex2FinX / bt.wMax, (double)(bt.hMax - bt.posTex2DebY) / bt.hMax);
        glVertex2d(bt.posX + bt.weight, FENETRE_HAUT - bt.posY);
        glTexCoord2d((double)bt.posTex2FinX / bt.wMax, (double)(bt.hMax - bt.posTex2FinY) / bt.hMax);
        glVertex2d(bt.posX + bt.weight, (FENETRE_HAUT - bt.posY) - bt.height);
        glTexCoord2d((double)bt.posTex2DebX / bt.wMax, (double)(bt.hMax - bt.posTex2FinY) / bt.hMax);
        glVertex2d(bt.posX, (FENETRE_HAUT - bt.posY) - bt.height);
    }
    else
    {
        glTexCoord2d((double)bt.posTex1DebX / bt.wMax, (double)(bt.hMax - bt.posTex1DebY) / bt.hMax);
        glVertex2d(bt.posX, FENETRE_HAUT - bt.posY);
        glTexCoord2d((double)bt.posTex1FinX / bt.wMax, (double)(bt.hMax - bt.posTex1DebY) / bt.hMax);
        glVertex2d(bt.posX + bt.weight, FENETRE_HAUT - bt.posY);
        glTexCoord2d((double)bt.posTex1FinX / bt.wMax, (double)(bt.hMax - bt.posTex1FinY) / bt.hMax);
        glVertex2d(bt.posX + bt.weight, (FENETRE_HAUT - bt.posY) - bt.height);
        glTexCoord2d((double)bt.posTex1DebX / bt.wMax, (double)(bt.hMax - bt.posTex1FinY) / bt.hMax);
        glVertex2d(bt.posX, (FENETRE_HAUT - bt.posY) - bt.height);
    }
    glEnd();

    if(bt.texte.chaine != NULL)
    {
        glTranslated(0, 0, 2);
        posTexteX = bt.posX + bt.weight / 2 - recupererLargeurChaine(bt.texte, largeurLettre) / 2;
        posTexteY = bt.posY + bt.height / 2 - 8;
        afficherTexte(texTexte, bt.texte, largeurLettre, 1, posTexteX, posTexteY);
    }
}

void collisionBouton(Bouton *bouton)
{
    if(event.posX >= bouton->posX && event.posX <= bouton->posX + bouton->weight)
    {
        if(event.posY >= bouton->posY && event.posY <= bouton->posY + bouton->height)
        {
            bouton->selectionne = 1;
        }
        else
        bouton->selectionne = 0;
    }
    else
        bouton->selectionne = 0;
}

int recupererLargeurChaine(Texte chaine, int largeurLettre[255])
{
    int i;
    int largeur = 0;

    for(i = 0; i < chaine.nbCara; i++)
    {
        if(chaine.chaine[i] != 0)
            largeur += largeurLettre[(int)chaine.chaine[i]] + 2;
    }

    return largeur;
}

int eventCommande(int *touche)
{
    int i;
    int c = 0;

    for(i = 0; i < SDLK_LAST; i++)
    {
        if(event.touche[i] == 1)
        {
            if(i != 0 && i != SDLK_ESCAPE)
            {
                c = i;
                event.touche[i] = 0;
            }
        }
    }

    for(i = 0; i < 8; i++)
    {
        if(event.souris[i] == 1)
        {
            if(i != SDL_BUTTON_WHEELDOWN && i != SDL_BUTTON_WHEELUP)
            {
                c = i;
                event.souris[i] = 0;
            }
        }
    }

    (*touche) = c;

    return c;
}

void attribuerNomBoutonControle(Texte *nomBouton, int valeur)
{
    if(valeur < 8)
    {
        switch(valeur)
        {
            case SDL_BUTTON_LEFT:
                nomBouton->nbCara = 8;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "Button 1");
                break;
            case SDL_BUTTON_MIDDLE:
                nomBouton->nbCara = 8;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "Button 3");
                break;
            case SDL_BUTTON_RIGHT:
                nomBouton->nbCara = 8;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "Button 2");
                break;
            default:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "?");
                break;
        }
    }
    else
    {
        switch(valeur)
        {
            case SDLK_a:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "A");
                break;
            case SDLK_b:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "B");
                break;
            case SDLK_c:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "C");
                break;
            case SDLK_d:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "D");
                break;
            case SDLK_e:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "E");
                break;
            case SDLK_f:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F");
                break;
            case SDLK_g:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "G");
                break;
            case SDLK_h:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "H");
                break;
            case SDLK_i:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "I");
                break;
            case SDLK_j:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "J");
                break;
            case SDLK_k:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "K");
                break;
            case SDLK_l:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "L");
                break;
            case SDLK_m:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "M");
                break;
            case SDLK_n:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "N");
                break;
            case SDLK_o:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "O");
                break;
            case SDLK_p:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "P");
                break;
            case SDLK_q:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "Q");
                break;
            case SDLK_r:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "R");
                break;
            case SDLK_s:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "S");
                break;
            case SDLK_t:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "T");
                break;
            case SDLK_u:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "U");
                break;
            case SDLK_v:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "V");
                break;
            case SDLK_w:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "W");
                break;
            case SDLK_x:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "X");
                break;
            case SDLK_y:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "Y");
                break;
            case SDLK_z:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "Z");
                break;
            case SDLK_SPACE:
                nomBouton->nbCara = 5;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "SPACE");
                break;
            case SDLK_TAB:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "TAB");
                break;
            case SDLK_LSHIFT:
                nomBouton->nbCara = 6;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "LSHIFT");
                break;
            case SDLK_RSHIFT:
                nomBouton->nbCara = 6;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "RSHIFT");
                break;
            case SDLK_LALT:
                nomBouton->nbCara = 4;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "LALT");
                break;
            case SDLK_RALT:
                nomBouton->nbCara = 4;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "RALT");
                break;
            case SDLK_RCTRL:
                nomBouton->nbCara = 5;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "RCTRL");
                break;
            case SDLK_LCTRL:
                nomBouton->nbCara = 5;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "LCTRL");
                break;
            case SDLK_MENU:
                nomBouton->nbCara = 4;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "MENU");
                break;
            case SDLK_END:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "END");
                break;
            case SDLK_BACKSPACE:
                nomBouton->nbCara = 9;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "BACKSPACE");
                break;
            case SDLK_PAGEDOWN:
                nomBouton->nbCara = 4;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "NEXT");
                break;
            case SDLK_PAGEUP:
                nomBouton->nbCara = 8;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "PREVIOUS");
                break;
            case SDLK_F1:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F1");
                break;
            case SDLK_F2:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F2");
                break;
            case SDLK_F3:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F3");
                break;
            case SDLK_F4:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F4");
                break;
            case SDLK_F5:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F5");
                break;
            case SDLK_F6:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F6");
                break;
            case SDLK_F7:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F7");
                break;
            case SDLK_F8:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F8");
                break;
            case SDLK_F9:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F9");
                break;
            case SDLK_F10:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F10");
                break;
            case SDLK_F11:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F11");
                break;
            case SDLK_F12:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F12");
                break;
            case SDLK_F13:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F13");
                break;
            case SDLK_F14:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F14");
                break;
            case SDLK_F15:
                nomBouton->nbCara = 3;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "F15");
                break;
            case SDLK_EQUALS:
                nomBouton->nbCara = 6;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "EQUALS");
                break;
            case SDLK_COMMA:
                nomBouton->nbCara = 5;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "COMMA");
                break;
            case SDLK_RIGHT:
                nomBouton->nbCara = 5;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "RIGHT");
                break;
            case SDLK_LEFT:
                nomBouton->nbCara = 4;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "LEFT");
                break;
            case SDLK_UP:
                nomBouton->nbCara = 2;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "UP");
                break;
            case SDLK_DOWN:
                nomBouton->nbCara = 4;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "DOWN");
                break;
            default:
                nomBouton->nbCara = 1;
                nomBouton->chaine = malloc((nomBouton->nbCara + 1) * sizeof(char));
                sprintf(nomBouton->chaine, "?");
                break;
        }
    }
}

int verifierEvenement(int evenement)
{
    int vrai = 0;

    if(evenement < 8)
    {
        if(event.souris[evenement] == 1)
            vrai = 1;
    }
    else
    {
        if(event.touche[evenement] == 1)
            vrai = 1;
    }

    return vrai;
}

void supprimerEvenement(int evenement)
{
    if(evenement < 8)
    {
        event.souris[evenement] = 0;
    }
    else
    {
        event.touche[evenement] = 0;
    }
}

int collisionDecor(Chunk *terrain, double x, double y, double z)
{
    int collision = 0;
    int posX = (int)x % TAILLECHUNK_X, posY = (int)y % TAILLECHUNK_Y, posZ = (int)z % TAILLECHUNK_Z;

    if(posX >= 0 && posY >= 0 && posZ >= 0 && posX < TAILLECHUNK_X && posY < TAILLECHUNK_Y && posZ < TAILLECHUNK_Z)
    {
        if(terrain->entite[posX][posY][posZ] != 0)
            collision = 1;
    }

    return collision;
}

void dessinerSkyBox(Pave *SkyBox)
{
    int i;

    glBegin(GL_QUADS);

    for(i = 0; i < 6; i++)
    {
        glColor3ub(200 - i * 20, 200 - i * 20, 200 - i * 20);
        glVertex3d(SkyBox->face[i].bas1.x, SkyBox->face[i].bas1.y, SkyBox->face[i].bas1.z);
        glVertex3d(SkyBox->face[i].bas2.x, SkyBox->face[i].bas2.y, SkyBox->face[i].bas2.z);
        glVertex3d(SkyBox->face[i].haut2.x, SkyBox->face[i].haut2.y, SkyBox->face[i].haut2.z);
        glVertex3d(SkyBox->face[i].haut1.x, SkyBox->face[i].haut1.y, SkyBox->face[i].haut1.z);
    }

    glEnd();
}

void afficherItem(Item *items, int ID, int IDTexItems)
{
    Texture texItem;
    int i;

    texItem.IDtex = IDTexItems;

    texItem.weight = 32;
    texItem.height = 32;
    texItem.wMax = 512;
    texItem.hMax = 512;
    texItem.posX = 0;
    texItem.posY = 0;

    for(i = 0; i < NOMBRE_ITEMS; i++)
    {
        if(items[i].ID == ID)
        {
            texItem.posTexY = (items[i].IDTex / 16) * texItem.weight;
            texItem.posTexX = (items[i].IDTex - items[i].IDTex / 16 * 16) * texItem.height;
            afficherTexture(texItem);
        }
    }
}

int retrouverChunk(Map *map, int cibleChunkX, int cibleChunkZ, int *indiceChunk)
{
    int i;
    int existant = -1;

    for(i = 0; i < CHUNK_MEM * CHUNK_MEM; i++)
    {
        if(map->chunk[i].posX == cibleChunkX && map->chunk[i].posZ == cibleChunkZ)
        {
            if(indiceChunk != NULL)
            {
                (*indiceChunk) = i;
            }
            existant = 1;
        }
    }

    return existant;
}

void dessinerMain(Inventaire *inv, int blocActuel)
{

}
