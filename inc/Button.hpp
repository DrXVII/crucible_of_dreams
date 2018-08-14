#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
using std::string;

//3rd party libs
#include <SDL2/SDL.h>

//homebrew
#include "dbg.h"
#include "Font_atlas.hpp"

/* TODO This is a work in progress,
 * texture handle changing and other things are
 * still to be implemented/designed */

class Button {
public:
    Button(string const& _txt, Font_atlas* _font,
           SDL_Texture* _tx, SDL_Texture* _tx_p,
           int _x, int _y);
    //~Button();

    void render(SDL_Renderer* _ren);
    bool check_click(int _x, int _y);

    void press();
    void unpress();

    //set texture(s)
    void set_tx(
            SDL_Texture* _tx,
            SDL_Texture* _tx_press,
            SDL_Texture* _tx_disab,
            SDL_Texture* _tx_sel);
    void set_rect(SDL_Rect* _rect);
    void set_xy(int _x, int _y);
    void set_txt(string const& _txt);
    void sync_wh_to_tx(); //set width and height of rect to that of loaded texture

private:
    Font_atlas* font;
    SDL_Texture* tx; //the default button appearance
    SDL_Texture* tx_press; //when the button is pressed down
    SDL_Texture* tx_disp; //the current active texture of the button
    string txt; //the button text
    int txt_x_offs; //the offset of button text
    int txt_y_offs; //the offset of button text
    SDL_Rect rect;
};


#endif //define BUTTON_HPP
