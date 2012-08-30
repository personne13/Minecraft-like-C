#ifndef OBJ
#define OBJ

    void attribuerCube(Pave *cube, double dimension);
    void attribuerPersonnage(Mob *personnage, GLuint tex);
    void dessinerPersonnage(Mob personnage, double angleMembres, double angleTeteY, double angleTeteX);
    void chargerItems(Item *items, char *chemin);

#endif
