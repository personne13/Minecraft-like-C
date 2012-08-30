#ifndef INPUT
#define INPUT

    typedef struct
    {
        char touche[SDLK_LAST];
        char toucheUni[SDLK_LAST];
        int posX,posY;
        int xrel,yrel;
        char souris[8];
        char quitter;

    } Input;

    void updateEvents(Input* in);
    void initialiserInput(Input *in);

#endif
