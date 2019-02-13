#include "Tilemap.hpp" //header for this implementation file

#include "dbg.h"

Tilemap::Tilemap(size_t w, size_t h)
: m_w {w}
, m_h {h}
{
    m_tiles = vector<vector<Tile*>>(w, vector<Tile*>(h));
}

void Tilemap::put_tile(Tile* tile, size_t x, size_t y)
{
    if(x < m_w && y < m_h) {
        dbgf(10, "putting tile at: %lu/%lu\n", x, y);
        m_tiles[x][y] = tile;
    }
    else {dbgf(1, "could not put tile - out of tilemap range\n");}
}

void Tilemap::render(int x, int y, int w, int h,
        SDL_Renderer* ren)
{
    SDL_Point ren_pt {x, y};
    for(size_t arr_x = 0; arr_x < m_tiles.size(); ++arr_x) {
        size_t tile_w {0};

        for(size_t arr_y = 0; arr_y < m_tiles[arr_x].size(); ++arr_y) {
            if(m_tiles[arr_x][arr_y]) {
                m_tiles[arr_x][arr_y]->render(ren, &ren_pt);
            }
            else {dbgf(1,"request to render nullren_ptr tile\n");}
            //dbgf(1, "render request at %d/%d\n");

            ren_pt.y += m_tiles[arr_x][arr_y]->get_h();
            tile_w = m_tiles[arr_x][arr_y]->get_w();

            if(ren_pt.y >= h) {break;}
        }
        ren_pt.y = y;

        ren_pt.x += tile_w;
        if(ren_pt.x >= w) {break;}
    }
}

size_t Tilemap::get_w() {return m_w;}

size_t Tilemap::get_h() {return m_h;}
