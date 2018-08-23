#include "Button.hpp"

/* constructor for uninitialized button (e.g. for fast & easy array init, etc)
 * of course, afterwards, the button should not be used uninitialised */
Button::Button() {};

Button::Button(string const& _txt, Font_atlas* _font,
        SDL_Texture* _tx, SDL_Texture* _tx_p,
        int _x, int _y)
: rect {_x, _y, 0, 0}
, font {_font}
, tx {_tx}
, tx_press {_tx_p}
, tx_disp {this->tx}
, on_click {nullptr}
, on_rel {nullptr}
, txt_x_offs {0}
, txt_y_offs {0}
, pressed {false}
, txt {_txt}
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

bool Button::click(void* _data)
{
    //nothing to do if click not within bounding box
    if(this->check_mouse_coll() == false) { return false; }

    this->press();
    if(this->on_click != nullptr) { this->on_click(_data); }

    return true;
}

bool Button::unclick(void* _data)
{
    this->unpress();
    //execute release callback if mouse unclicked within bounding box
    if(this->check_mouse_coll()) {
        if(this->on_rel != nullptr) { this->on_rel(_data); }
        return true;
    }

    return false;
}

void Button::press() {
    if(this->pressed == false) {
        this->tx_disp = this->tx_press;
        this->txt_x_offs += this->rect.h / 20;
        this->txt_y_offs += this->rect.h / 20;
        this->pressed = true;
    }
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

void Button::set_on_click(void (*_on_click)(void*)){this->on_click = _on_click;}
void Button::set_on_rel(void (*_on_rel)(void*)) { this->on_rel = _on_rel; }

void Button::sync_wh_to_tx()
{
    SDL_QueryTexture(this->tx, NULL, NULL, &this->rect.w, &this->rect.h);
}

bool Button::check_coll(int _x, int _y)
{
    if(_x < this->rect.x ||
       _x > this->rect.x + this->rect.w ||
       _y < this->rect.y ||
       _y > this->rect.y + this->rect.h)
    {
        return false;
    }
    else {
        return true;
    }
}

bool Button::check_mouse_coll()
{
    int x,y;
    SDL_GetMouseState(&x, &y);

    return this->check_coll(x, y);
}
