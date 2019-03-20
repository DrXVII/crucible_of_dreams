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

//TODO think on concept and probably rename to Area_map
//TODO Tilemap should have a Tileset within it
class Tilemap {
public:
    Tilemap(size_t w, size_t h);

    void put_tile(Tile* tile, size_t x, size_t y);
    void render(int x, int y, int w, int h, SDL_Renderer* ren);
    void highlight_mouseover(SDL_Renderer* ren, Tile* selected_gfx);

    size_t get_w();
    size_t get_h();
private:
    //TODO m_viewport is not used yet in implementation, use is planned
    U_rect m_viewport;
    size_t m_w;
    size_t m_h;
    vector<vector<Tile*>> m_tiles;
    //vector<vector<Wall*>> walls;
    //vector<vector<Interact_object*>> objects;
    //vector<vector<Event_trigger*>> events;
};
