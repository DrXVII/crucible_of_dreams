#ifndef WALL_HPP
#define WALL_HPP

//third party libs
#include <SDL2/SDL.h>

//homebrew
#include "Tile.hpp"

namespace cru {

class Wall : public Tile {
public:
    Wall(SDL_Texture* tx = nullptr, int w = 0, int h = 0,
            Direction dir = NORTH);
};

}

#endif //ifndef WALL_HPP
