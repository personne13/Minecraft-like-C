#ifndef TEXTE
#define TEXTE

    void saisirTexte(char texte[]);
    char interpreterEvent();
    void afficherTexte(GLuint texture, Texte texte, int *largeurLettre, double taillePolice, int x, int y);
    void chargerLargeurLettres(char *chemin, int largeurLettre[255]);

#endif
