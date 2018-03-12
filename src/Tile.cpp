#include "Tile.hpp" //header for this implementation file

Tile::Tile(SDL_Texture* _tx, int _w, int _h)
: w {_w}
, h {_h}
, tx {_tx}
{
    if(this->tx != nullptr && this->w == 0 && this->h == 0) {
        this->wh_to_tx();
    }
}

int Tile::wh_to_tx()
{
    return SDL_QueryTexture(this->tx, NULL, NULL, &this->w, &this->h);
}

void Tile::render(SDL_Renderer* _ren, SDL_Point* _pt)
{
    SDL_Rect rect {_pt->x, _pt->y, this->w, this->h};
    if(SDL_RenderCopy(_ren, this->tx, NULL, &rect) != 0) {
        errlog(ERRLOG_SDL, "could not render tile.");
    }
}
