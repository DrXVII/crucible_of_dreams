#ifndef TILE_HPP
#define TILE_HPP

//third party libs
#include <SDL2/SDL.h>

//homebrew
#include "dbg.h"
#include "structs.hpp"

enum Direction {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};

class Tile {
public:
    Tile(SDL_Texture* _tx = nullptr, int _w = 0, int _h = 0,
            Direction orientation = NORTH);
    virtual ~Tile();

    //set w and h to match texture dimensions
    int wh_to_tx();
    //TODO rendering should be handled by cru::Viewport
    void render(SDL_Renderer* _ren, SDL_Point* _pt);
    void render(SDL_Renderer* ren, int x, int y);
    int get_w();
    int get_h();

private:
    cru::Point m_anchor; //TODO use to center anchor on node for rendering
    SDL_Texture* m_tx;
    Direction m_orientation;
    int m_w, m_h;
};

#endif //define TILE_HPP
