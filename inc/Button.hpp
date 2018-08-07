#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
using std::string;

//3rd party libs
#include <SDL2/SDL.h>

//homebrew
#include "dbg.h"

/* TODO This is a work in progress,
 * texture handle changing and other things are
 * still to be implemented/designed */

class Button {
public:
    Button(string const& _txt, SDL_Texture* _tx, int _x, int _y);
    //~Button();

    void render(SDL_Renderer* _ren);

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
    SDL_Texture* tx; //the default button appearance
    SDL_Texture* tx_press; //when the button is pressed down
    //shared_ptr<SDL_Texture> tx_disab; //when the button is disabled
    //shared_ptr<SDL_Texture> tx_sel; //when button is sellected (e.g. mouse-over)
    SDL_Rect rect;
    string txt; //the button text
};


#endif //define BUTTON_HPP
