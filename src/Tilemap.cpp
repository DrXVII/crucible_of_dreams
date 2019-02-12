#include "Tilemap.hpp" //header for this implementation file

Tilemap::Tilemap(unsigned i_w, unsigned i_h)
: w {i_w}
, h {i_h}
{
    tiles = vector<vector<Tile*>>(i_w, vector<Tile*>(i_h));
}

//void Tilemap::render(unsigned x, unsigned y, unsigned w, unsigned h,
//        SDL_Renderer ren)
//{
//}
