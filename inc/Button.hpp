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
    Button(string const& _txt, SDL_Texture* _tx);
    //~Button();

    void render(SDL_Renderer* _ren);

    //set texture(s)
    void set_tx(
            SDL_Texture* _tx,
            SDL_Texture* _tx_press,
            SDL_Texture* _tx_disab,
            SDL_Texture* _tx_sel);
    void set_rect(SDL_Rect* _rect);
    //TODO void set_wh_from_tx(); //get width and height of rect from loaded texture
    void set_txt(string const& _txt);

private:
    SDL_Texture* tx; //the default button appearance
    SDL_Texture* tx_press; //when the button is pressed down
    //shared_ptr<SDL_Texture> tx_disab; //when the button is disabled
    //shared_ptr<SDL_Texture> tx_sel; //when button is sellected (e.g. mouse-over)
    SDL_Rect rect;
    string txt; //the button text
};


#endif //define BUTTON_HPP
