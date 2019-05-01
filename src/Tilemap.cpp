#include "Tilemap.hpp" //header for this implementation file

//homebrew
#include "utils.hpp"
#include "dbg.h"

Tilemap::Tilemap(size_t w, size_t h, size_t tile_w, size_t tile_h)
: m_w {w}
, m_h {h}
, m_tile_w {tile_w}
, m_tile_h {tile_h}
{
    m_tiles = vector<vector<Tile*>>(w, vector<Tile*>(h));
}

/*TODO - incorporate Tileset(TODO - create) into Tilemap, selected_gfx should
 * be in the Tilemap object, probably in the Tileset object*/
//TODO - highlight moused-over tile position only when within Tilemap bounds
//void Tilemap::highlight_mouseover(SDL_Renderer* ren, Tile* selected_gfx)
//{
//    int x, y;
//    SDL_GetMouseState(&x, &y);
//
//    int tile_w = m_tiles[0][0]->get_w();
//    int tile_h = m_tiles[0][0]->get_h();
//
//    //getting upper left corner of tile the mouse is over
//    int screen_coord_x = (x / tile_w) * tile_w;
//    int screen_coord_y = (y / tile_h) * tile_h;
//
//    /*TODO just proof of concept, should define and use Tilemap->viewport to
//get x, y, w, h*/
//    if(collision_check_box_pt(0, 0, (m_w * tile_w) - 1, (m_h * tile_h) - 1, x, y)) {
//        selected_gfx->render(ren, screen_coord_x, screen_coord_y);
//    }
//}

void Tilemap::put_tile(Tile* tile, size_t x, size_t y)
{
    if(x < m_w && y < m_h) {
        dbgf(10, "putting tile at: %lu/%lu\n", x, y);
        m_tiles[x][y] = tile;
    }
    else {dbgf(1, "could not put tile - out of tilemap range\n");}
}

//TODO this is a quick & dirty solution, needs review
void Tilemap::render(int x, int y, int w, int h,
        SDL_Renderer* ren)
{
    SDL_Point ren_pt {x, y};
    for(size_t arr_x = 0; arr_x < m_tiles.size(); ++arr_x) {
        for(size_t arr_y = 0; arr_y < m_tiles[arr_x].size(); ++arr_y) {
            if(m_tiles[arr_x][arr_y]) {
                m_tiles[arr_x][arr_y]->render(ren, &ren_pt);
            }

            ren_pt.y += m_tile_h /2;
            ren_pt.x -= m_tile_w /2;

            if(ren_pt.x >= w) {break;}
            else if(ren_pt.x < 0) {break;}
            else if(ren_pt.y >= h) {break;}
        }

        //move the row-top position down and right by half of a tile
        ren_pt.y = y + m_tile_h * arr_x /2;
        ren_pt.x = x + m_tile_w * arr_x /2;
        if(ren_pt.x >= w) {break;}
    }
}

void Tilemap::render(cru::Rect rect, SDL_Renderer* ren)
{
    this->render(rect.x, rect.y, rect.w, rect.h, ren);
}

size_t Tilemap::get_w() {return m_w;}

size_t Tilemap::get_h() {return m_h;}
