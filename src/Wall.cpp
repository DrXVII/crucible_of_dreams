#include "Wall.hpp"

using namespace cru;

Wall::Wall(SDL_Texture* tx, int w, int h, Direction dir)
{
    Tile(tx, w, h, dir);
}
