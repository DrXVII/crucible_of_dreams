#include "Tile.hpp" //header for this implementation file

Tile::Tile(SDL_Texture* _tx, int _w, int _h)
: m_w {_w}
, m_h {_h}
, m_tx {_tx}
{
    if(m_tx != nullptr && (m_w == 0 || m_h == 0)) {
        this->wh_to_tx();
    }
}

int Tile::wh_to_tx()
{
    return SDL_QueryTexture(this->m_tx, NULL, NULL, &m_w, &m_h);
}

void Tile::render(SDL_Renderer* _ren, SDL_Point* _pt)
{
    SDL_Rect rect {_pt->x, _pt->y, m_w, m_h};
    if(SDL_RenderCopy(_ren, m_tx, NULL, &rect) != 0) {
        errlog(ERRLOG_SDL, "could not render tile.");
    }
}

int Tile::get_w() {return m_w;}

int Tile::get_h() {return m_h;}
