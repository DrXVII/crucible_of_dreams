#include "Button.hpp"

Button::Button(string const& _txt, Font_atlas* _font,
        SDL_Texture* _tx, SDL_Texture* _tx_p,
        int _x, int _y)
: rect {_x, _y, 0, 0}
, font {_font}
, tx {_tx}
, tx_press {_tx_p}
, tx_disp {this->tx}
, txt {_txt}
, txt_x_offs {0}
, txt_y_offs {0}
, pressed {false}
{
    if(this->tx != nullptr) {
        this->sync_wh_to_tx();
        //calculating offsets to print the text in the centre of the button
        this->txt_x_offs =
                (this->rect.w - (this->font->get_w() * this->txt.size())) / 2;
        this->txt_y_offs = (this->rect.h - this->font->get_h()) / 2;
    }

    dbgf(0, "created button \"%s\"\n", this->txt.c_str());
};

Button::~Button()
{
    dbgf(9, "destroying button \"%s\"\n", this->txt.c_str());
}

void Button::render(SDL_Renderer* _ren)
{
    if(SDL_RenderCopy(_ren, this->tx_disp, NULL, &this->rect) != 0) {
        errlog(ERRLOG_SDL, "could not render button.");
    }


    this->font->print(this->txt.c_str(),
            this->rect.x + this->txt_x_offs, this->rect.y + this->txt_y_offs,
            _ren);
}

bool Button::check_click(int _x, int _y)
{
    if(_x < this->rect.x ||
       _x > this->rect.x + this->rect.w ||
       _y < this->rect.y ||
       _y > this->rect.y + this->rect.h)
    {
        return false;
    }
    else { return true; }
}

void Button::press() {
    this->tx_disp = this->tx_press;
    this->txt_x_offs += this->rect.h / 20;
    this->txt_y_offs += this->rect.h / 20;
    this->pressed = true;
}
void Button::unpress() {
    if(this->pressed) {
        this->tx_disp = this->tx;
        this->txt_x_offs -= this->rect.h / 20;
        this->txt_y_offs -= this->rect.h / 20;
        this->pressed = false;
    }
}

void Button::set_tx( SDL_Texture* _tx, SDL_Texture* _tx_press)
{
    this->tx = _tx;
    this->tx_press = _tx_press;

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
