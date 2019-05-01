#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "Tilemap.hpp"
#include "Tile.hpp"
#include "Wall.hpp"

namespace cru {

class Level {
public:
    Level(size_t w, size_t h, size_t tile_w, size_t tile_h);
    Level(Tilemap* floor);

    //void move_chars();
    void load_test_level();
    void load_test_assets(SDL_Renderer* ren);

private:
    std::vector<Tile> m_tileset;
    Tilemap m_floor;
    Tilemap m_walls;
    //std::vector<Character*> m_characters;

    friend class Viewport;
};

}

#endif //ifndef LEVEL_HPP
