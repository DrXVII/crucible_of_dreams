//third party libs
#include <SDL2/SDL.h>

//homebrew
#include "dbg.h"

class Tile {
public:
    Tile(SDL_Texture* _tx = nullptr, int _w = 0, int _h = 0);

    //set w and h to match texture dimensions
    int wh_to_tx();
    void render(SDL_Renderer* _ren, SDL_Point* _pt);

private:
    int w, h;
    SDL_Texture* tx;
};
