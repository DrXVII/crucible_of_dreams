#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Tilemap.hpp"

namespace cru {

class Level {
public:
    Level(Tilemap* floor);
    void move_chars();
private:
    Tilemap* m_floor;
    //std::vector<Wall*> m_walls;
    //std::vector<Character*> m_characters;

    friend class Viewport;
};

}

#endif //ifndef LEVEL_HPP
