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

//TODO think on concept and probably rename to Area_map
//TODO Tilemap should have a Tileset within it
class Tilemap {
public:
    Tilemap(size_t w, size_t h);

    void put_tile(Tile* tile, size_t x, size_t y);
    //TODO remove render_old
    void render_old(int x, int y, int w, int h, SDL_Renderer* ren);
    void render(int x, int y, int w, int h, SDL_Renderer* ren);
    void render(cru::Rect, SDL_Renderer* ren);
    //TODO tile highlight should be the responsibility of cru::Viewport
    void highlight_mouseover(SDL_Renderer* ren, Tile* selected_gfx);

    size_t get_w();
    size_t get_h();
private:
    size_t m_w;
    size_t m_h;
    vector<vector<Tile*>> m_tiles;
    //vector<vector<Wall*>> walls;
    //vector<vector<Interact_object*>> objects;
    //vector<vector<Event_trigger*>> events;
};

#endif //ifndef TILEMAP_HPP
