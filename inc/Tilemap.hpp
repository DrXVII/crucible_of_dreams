//std c++ lib
#include <vector>
using std::vector;

//homebrew
#include "Tile.hpp"

//TODO think on concept and probably rename to Area_map
class Tilemap {
public:
    Tilemap(size_t w, size_t h);

    void put_tile(Tile* tile, size_t x, size_t y);
    void render(int x, int y, int w, int h, SDL_Renderer* ren);

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
