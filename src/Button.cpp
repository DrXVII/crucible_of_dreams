#include "Button.hpp"

Button::Button(string const& _txt, SDL_Texture* _tx, int _x, int _y)
: tx {_tx}
, tx_press {nullptr}
, rect {_x, _y, 0, 0}
, txt {_txt}
{
    if(this->tx != nullptr) { this->sync_wh_to_tx(); }

    dbgf(0, "created button \"%s\"\n", this->txt.c_str());
};

void Button::render(SDL_Renderer* _ren)
{
    if(SDL_RenderCopy(_ren, this->tx, NULL, &this->rect) != 0) {
        errlog(ERRLOG_SDL, "could not render button.");
    }
}

void Button::set_tx(
        SDL_Texture* _tx,
        SDL_Texture* _tx_press,
        SDL_Texture* _tx_disab __attribute__((unused)),
        SDL_Texture* _tx_sel __attribute__((unused)))
{
    this->tx = _tx;
    this->tx_press = _tx_press;
    //this->tx_disab = _tx_disab;
    //this->tx_sel = _tx_sel;

    if(this->tx != nullptr) { this->sync_wh_to_tx(); }
}

void Button::set_rect(SDL_Rect* _rect)
{
    this->rect = *_rect;
}

void Button::set_xy(int _x, int _y)
{
    this->rect.x = _x;
    this->rect.y = _y;
}

void Button::set_txt(string const& _txt)
{
    this->txt = _txt;
}

void Button::sync_wh_to_tx()
{
    SDL_QueryTexture(this->tx, NULL, NULL, &this->rect.w, &this->rect.h);
}
