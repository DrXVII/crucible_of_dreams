#ifndef TILEMAP_HPP
#define TILEMAP_HPP

//std c lib
#include <stddef.h>

//std c++ lib
#include <vector>
using std::vector;

//3rd party
#include <SDL2/SDL.h>

//homebrew
#include "Tile.hpp"
#include "gfx_structs.hpp"
#include "structs.hpp"

class Tilemap {
public:
    Tilemap(size_t w, size_t h, size_t tile_w, size_t tile_h);

    void put_tile(Tile* tile, size_t x, size_t y);
    //TODO rendering should be done by cru::Viewport
    void render(int x, int y, int w, int h, SDL_Renderer* ren);
    void render(cru::Rect, SDL_Renderer* ren);

    size_t get_w();
    size_t get_h();
private:
    size_t m_w; //how many tiles on the x axis
    size_t m_h; //how many tiles on the y axis
    size_t m_tile_w; //width of one tile in px
    size_t m_tile_h; //height of one tile in px
    vector<vector<Tile*>> m_tiles;
};

#endif //ifndef TILEMAP_HPP
