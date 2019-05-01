#include "Level.hpp"

#include "utils.hpp"

using namespace cru;

Level::Level(size_t w, size_t h, size_t tile_w, size_t tile_h)
:m_floor {Tilemap(w, h, tile_w, tile_h)}
,m_walls {Tilemap(w*2 - 1, h*2 - 1, tile_w/2, tile_h/2)}
{}

enum {SELECTED = 0, COBBLE, WALL, WALL_E, TILESET_SIZE};
void Level::load_test_assets(SDL_Renderer* ren)
{
    m_tileset.resize(TILESET_SIZE, Tile());
    m_tileset[SELECTED] =
        Tile(load_texture("data/gfx/tiles/tile_selected.png", ren));
    m_tileset[COBBLE] =
        Tile(load_texture("data/gfx/tiles/floor_cobble.png", ren));
    m_tileset[WALL] =
        Tile(load_texture("data/gfx/tiles/floor_wall.png", ren));
    m_tileset[WALL_E] =
        Tile(load_texture("data/gfx/tiles/floor_wall.png", ren), 0, 0, EAST);

}

void Level::load_test_level()
{
    for(size_t x = 0; x < m_floor.get_w(); ++x) {
        for(size_t y = 0; y < m_floor.get_h(); ++y) {
                m_floor.put_tile(&m_tileset[COBBLE], x, y);
            }
    }

    //making a square room
    SDL_Rect room_rect{20, 6, 9, 13};
    for(int x {0}; x < room_rect.w; ++x) {
        for(int y {0}; y < room_rect.h; ++y) {
            if(x == 0 || x == room_rect.w - 1) {
                m_walls.put_tile(&m_tileset[WALL_E],
                        room_rect.x + x, room_rect.y + y);
            }
            else if(y == 0 || y == room_rect.h - 1) {
                m_walls.put_tile(&m_tileset[WALL],
                        room_rect.x + x, room_rect.y + y);
            }
        }
    }
}
