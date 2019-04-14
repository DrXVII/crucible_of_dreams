#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <SDL2/SDL.h>

#include "Level.hpp"
#include "structs.hpp"

namespace cru {

//TODO move to dedicated file later
class Viewport {
public:
    Viewport (Level* level);

    void render(SDL_Renderer* ren);

    void set_screen_pos(cru::Rect r);

private:
    cru::Rect m_screen_pos;
    cru::Rect m_map_pos; //TODO use
    Level* m_level;
};

}

#endif //ifndef VIEWPORT_HPP
