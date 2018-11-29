//std c++ lib
#include <vector>
using std::vector;

//homebrew
#include "Tile.hpp"

//TODO think on concept and probably rename to Area_map
class Tilemap {
public:
    Tilemap(unsigned i_w, unsigned i_h);

    //render(unsigned i_x, unsigned i_y, unsigned i_w, unsigned i_h, SDL_Renderer i_ren);
private:
    unsigned w;
    unsigned h;
    vector<vector<Tile*>> tiles;
    //vector<vector<Wall*>> walls;
    //vector<vector<Interact_object*>> objects;
    //vector<vector<Event_trigger*>> events;
};
