#include "Viewport.hpp"

using namespace cru;

Viewport::Viewport(Level* level)
:m_screen_pos {0, 0, 0, 0}
,m_map_pos {0, 0, 0, 0}
,m_level {level}
{}

void Viewport::render(SDL_Renderer* ren)
{
    m_level->m_floor.render(m_screen_pos, ren);
    m_level->m_walls.render(m_screen_pos, ren);
}

void Viewport::set_screen_pos(cru::Rect r) { m_screen_pos = r; }
