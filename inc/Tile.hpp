#ifndef TILE_HPP
#define TILE_HPP

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
    int get_w();
    int get_h();

private:
    int m_w, m_h;
    SDL_Texture* m_tx;
};

#endif //define TILE_HPP
