#include "Button.hpp"

#include "utils.hpp"

/* constructor for uninitialized button (e.g. for fast & easy array init, etc)
 * of course, afterwards, the button should not be used uninitialised */
Button::Button() {};

Button::Button(string const& txt, Font_atlas* font,
        SDL_Texture* tx, SDL_Texture* tx_p,
        int x, int y)
: rect {x, y, 0, 0}
, font {font}
, tx {tx}
, tx_press {tx_p}
, tx_disp {this->tx}
, on_click {nullptr}
, on_rel {nullptr}
, txt_x_offs {0}
, txt_y_offs {0}
, pressed {false}
, txt {txt}
, mapped_key{0}
, use_key{false}
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

void Button::render(SDL_Renderer* ren)
{
    if(SDL_RenderCopy(ren, this->tx_disp, NULL, &this->rect) != 0) {
        errlog(ERRLOG_SDL, "could not render button.");
    }

    this->font->print(this->txt.c_str(),
            this->rect.x + this->txt_x_offs, this->rect.y + this->txt_y_offs,
            ren);
}

void Button::keypress(Uint8 keycode, void* data)
{
    if(this->use_key && keycode == this->mapped_key) {
        this->click(data, true);
    }
}

void Button::keyrel(Uint8 keycode, void* data)
{
    if(this->use_key && keycode == this->mapped_key) {
        this->unclick(data, true);
    }
}

bool Button::click(void* data, bool no_mouse_check)
{
    //refusing to click a button that is already clicked
    if(this->pressed) {return false;}

    bool mouseover = false;
    if(no_mouse_check) {mouseover = true;}
    else {mouseover = this->check_mouse_coll();}

    //nothing to do if click not within bounding box
    if(mouseover == false) { return false; }

    this->press();
    if(this->on_click != nullptr) { this->on_click(data); }

    return true;
}

bool Button::unclick(void* data, bool no_mouse_check)
{
    //refusing to unclick a button that is not clicked
    if(this->pressed == false) {return false;}

    this->unpress();

    bool mouseover = false;
    if(no_mouse_check) {mouseover = true;}
    else {mouseover = this->check_mouse_coll();}

    //execute on-release callback if mouse unclicked within bounding box
    if(mouseover) {
        if(this->on_rel != nullptr) { this->on_rel(data); }
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

void Button::set_tx( SDL_Texture* tx, SDL_Texture* tx_press)
{
    this->tx = tx;
    this->tx_press = tx_press;

    if(this->tx != nullptr) { this->sync_wh_to_tx(); }
}

void Button::set_rect(SDL_Rect* rect)
{
    this->rect = *rect;
}

void Button::set_xy(int x, int y)
{
    this->rect.x = x;
    this->rect.y = y;
}

void Button::set_txt(string const& txt)
{
    this->txt = txt;
}

void Button::set_on_click(void (*on_click)(void*)){this->on_click = on_click;}
void Button::set_on_rel(void (*on_rel)(void*)) {this->on_rel = on_rel;}

void Button::set_shortcut(Uint8 keycode) {
    this->mapped_key = keycode;
    this->enable_shortcut();
}
void Button::enable_shortcut() {this->use_key = true;}
void Button::disable_shortcut() {this->use_key = false;}

void Button::sync_wh_to_tx()
{
    SDL_QueryTexture(this->tx, NULL, NULL, &this->rect.w, &this->rect.h);
}

/*TODO things like box collision mechanics should be a general utility 
 * (utils.cpp ?)*/
//bool Button::check_coll(int x, int y)
//{
//    if(x < this->rect.x ||
//       x > this->rect.x + this->rect.w ||
//       y < this->rect.y ||
//       y > this->rect.y + this->rect.h)
//    {
//        return false;
//    }
//    else {
//        return true;
//    }
//}

bool Button::check_mouse_coll()
{
    int x,y;
    SDL_GetMouseState(&x, &y);

    return collision_check_box_pt(rect.x, rect.y, rect.w, rect.h, x, y);
}
