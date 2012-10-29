#ifndef JEUFPS
#define JEUFPS

    void jouer();
    void Dessiner(Point *direction, Point *position, double ay, double ax, Inventaire *inv, GLuint texture, GLuint gui[], GLuint textureTexte, int blocActuel, int modeDeJeu, int enJeu, int blocInvSelectionne, int IDblocInvSelectionne, int vision, int quantiteSelectionnee);
    void dessinerGui(Inventaire *inv, GLuint gui[], GLuint texture, int tailleCase, int blocActuel, int modeDeJeu, int enJeu, int blocInvSelectionne, int IDblocInvSelectionne, int quantiteSelectionnee);
    void deplacer(Map *map, Point *posObjet, Point *posCamera, double ax ,double ay);
    int retrouverChunk(Map *map, int cibleChunkX, int cibleChunkZ, int *indiceChunk);
    void determinerQuartile(int *quartile, double ay);
    double modulo(double nombre1,double nombre2);
    double radians(double angle);
    void regarder(Point *position, Point *direction);
    void tirer(Point A, Point B, Point *M);
    void determinerTir(Point A, Point B, Point *M);
    int collision(Point A, Point B, Map *map, Pave cible, Inventaire inv, int blocActuel, int placer);
    void afficherPoint(Point point);
    int determinerFaceCollision(Point A, Point B, Pave cible, double *portee);
    void redefinirPositionCube(Pave *cube, int dimension, int chunkX, int chunkZ, int x, int y, int z);
    int placerCube(Map *map, int colChunkX, int colChunkZ, int face, int x, int y, int z, int bloc);
    void casserCube(Chunk *terrain, int face, int x, int y, int z);
    void dessinerMiniatures(Inventaire *inv, GLuint texture, int tailleCase);
    void dessinerSkyBox(Pave *SkyBox);
    void afficherInventaire(Inventaire *inv, int modeDeJeu, GLuint gui[], GLuint textureTerrain, int blocInvSelectionne, int IDblocInvSelectionne, int quantiteSelectionnee);
    void afficherCubeMiniature(Pave cube, GLuint texture, int coef);
    void miniaturesInventaire(Inventaire *inv, int modeDeJeu, GLuint textureTerrain);
    int gererInventaire(Inventaire *inv, int modeDeJeu, int *IDblocInvSelectionne, int *quantiteSelectionnee);
    void afficherTexture(Texture texture);
    void attribuerTexGui(Texture texturesGui[], GLuint gui[]);
    void menu(GLuint texTexte, GLuint gui[], int largeurLettre[255]);
    void afficherBouton(Bouton bt, GLuint texTexte);
    void attribuerTexBouton(Bouton *bouton, GLuint gui[]);
    void collisionBouton(Bouton *bouton, int slider);
    int recupererLargeurChaine(Texte chaine, int largeurLettre[255]);
    int eventCommande(int *touche);
    void attribuerNomBoutonControle(Texte *nomBouton, int valeur);
    int verifierEvenement(int evenement);
    int recupererCoordonneesBoutons(char *cheminFichier, Bouton *bouton);
    void supprimerEvenement(int evenement);
    int collisionDecor(Chunk *terrain, double x, double y, double z);
    void afficherItem(Item *items, int ID, int IDTexItems);
    void dessinerMain(Inventaire *inv, int blocActuel);

#endif
