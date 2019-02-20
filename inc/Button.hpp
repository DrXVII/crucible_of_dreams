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
    Button(string const& txt, Font_atlas* font,
           SDL_Texture* tx, SDL_Texture* tx_p,
           int x, int y);
    ~Button();

    void render(SDL_Renderer* _ren);

    bool click(void* data, bool no_mouse_check = false);
    bool unclick(void* data, bool no_mouse_check = false);
    void keypress(Uint8 keycode, void* data);
    void keyrel(Uint8 keycode, void* data);
    //TODO the naming of these two is quite confusing
    void press();
    void unpress();

    void set_tx( SDL_Texture* tx, SDL_Texture* tx_press); //set texture(s)
    void set_rect(SDL_Rect* rect);
    void set_xy(int x, int y);
    void set_txt(string const& txt);
    void set_on_click(void (*on_click)(void*));
    void set_on_rel(void (*on_rel)(void*));
    void set_shortcut(Uint8 keycode); //set keyboard shortcut (SDL scancode or keycode)
    void enable_shortcut(); //enable use of keyboard shortcut
    void disable_shortcut(); //disable use of keyboard shortcut

    void sync_wh_to_tx(); //set width and height of rect to that of loaded texture
    bool check_mouse_coll();
    bool check_coll(int x, int y); //check for collision

private:
    SDL_Rect rect;
    Font_atlas* font;
    SDL_Texture* tx; //the default button appearance
    SDL_Texture* tx_press; //when the button is pressed down
    SDL_Texture* tx_disp; //the current active texture of the button
    //TODO having both on click and on release functions seems superfluous
    void (*on_click)(void*); //callback to execute on button click
    void (*on_rel)(void*); //callback to execute on button release
    int txt_x_offs; //the offset of button text
    int txt_y_offs; //the offset of button text
    bool pressed;
    string txt; //the button text
    Uint8 mapped_key; //keyboard key mapped to this button (aka. shortcut)
    bool use_key; //use keyboard shortcut
};


#endif //define BUTTON_HPP
