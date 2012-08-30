#ifndef MAP_MINE
#define MAP_MINE

    int chargerChunk(char *cheminDossier, Chunk *chunk, int x, int z);
    void dessinerChunk(Map *map, GLuint texture, int indiceChunk);
    void dessinerMap(Map *map, GLuint texture, int distanceRendue);
    void sauvegarderMapF(char *chemin, Chunk Terrain);
    void sauvegarderMap(char *cheminDossier, Map *map);
    void sauvegarderChunk(char *cheminDossier, Chunk *chunk);
    void dessinerCube(int IDbloc, char facesAffichables[6]);
    int chargerBlocs(char *chemin, Pave *bloc, int nombreBlocs);
    void initChunk(Chunk *chunk);
    void dessinerCubeVBO(GLuint *CubeBuffers);
    int chargerMap(char *cheminDossier, Map *map, double posX, double posZ, int distanceRendue);
    void gererChunk(Map *map, char *cheminDossier, double posX, double posZ);
    void libererChunk(Chunk *chunk);
    void creerChunk(char *cheminChunk, int chunkX, int chunkZ);

#endif
