#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
using std::string;

//3rd party libs
#include <SDL2/SDL.h>

//homebrew
#include "dbg.h"
#include "Font_atlas.hpp"

/*TODO LOW_PRI make it possible to emphasise a letter (e.g. different color
 * or bold) to represent keyboard shorcuts */

class Button {
public:
    Button();
    Button(string const& _txt, Font_atlas* _font,
           SDL_Texture* _tx, SDL_Texture* _tx_p,
           int _x, int _y);
    ~Button();

    void render(SDL_Renderer* _ren);

    bool click(void* _data);
    bool unclick(void* _data);
    void press();
    void unpress();

    //set texture(s)
    void set_tx( SDL_Texture* _tx, SDL_Texture* _tx_press);
    void set_rect(SDL_Rect* _rect);
    void set_xy(int _x, int _y);
    void set_txt(string const& _txt);
    void set_on_click(void (*_on_click)(void*));
    void set_on_rel(void (*_on_rel)(void*));
    void sync_wh_to_tx(); //set width and height of rect to that of loaded texture
    bool check_mouse_coll();
    bool check_coll(int _x, int _y); //check for collision

private:
    SDL_Rect rect;
    Font_atlas* font;
    SDL_Texture* tx; //the default button appearance
    SDL_Texture* tx_press; //when the button is pressed down
    SDL_Texture* tx_disp; //the current active texture of the button
    void (*on_click)(void*); //callback to execute on button click
    void (*on_rel)(void*); //callback to execute on button release
    int txt_x_offs; //the offset of button text
    int txt_y_offs; //the offset of button text
    bool pressed;
    string txt; //the button text
};


#endif //define BUTTON_HPP
