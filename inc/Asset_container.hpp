#ifndef ASSET_CONTAINER_HPP
#define ASSET_CONTAINER_HPP

//3rd party libs
#include <SDL2/SDL.h>

//homebrew
#include "utils.hpp"
#include "Font_atlas.hpp"

class Asset_container {
public:
    Asset_container(){};
    ~Asset_container();

    int load_fonts(SDL_Renderer* _ren, vector<string>* _paths);
    int load_textures(SDL_Renderer* _ren, vector<string>* _paths);

    SDL_Texture* get_tx(unsigned _pos);
    Font_atlas* get_font(unsigned _pos);
    
    void unload();
    void unload_textures();
    void unload_fonts();

private:
    vector<SDL_Texture*> txs; //textures
    vector<Font_atlas*> fonts; //fonts
    //store animations and other things here too in the future
};

#endif //define ASSET_CONTAINER_HPP
