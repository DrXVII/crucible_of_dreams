//c++ std lib
#include <string>
using std::string;

#ifndef FONT_ATLAS_HPP
#define FONT_ATLAS_HPP
//c++ std lib
#include <string>
using std::string;

//homebrew
#include "Texture_obj.hpp"
#include "utils.hpp"
#include "dbg.h"

//there are 95 printable characters in ASCII table (positions 32-126)
#define FONT_ATLAS_TX_ARR_START 32
#define FONT_ATLAS_TX_ARR_END 126
#define FONT_ATLAS_TX_ARR_LEN (FONT_ATLAS_TX_ARR_END-FONT_ATLAS_TX_ARR_START +1)

class Font_atlas {
public:
    Font_atlas(string const& _fpath, int _sz, SDL_Renderer* _ren);
    ~Font_atlas();

    //render text with _ren
    int print(string const& _txt, SDL_Point* _xy, SDL_Renderer* _ren);

#ifdef DEBUG
    void test(SDL_Renderer* _ren);
#endif //#ifdef DEBUG

private:
    int fill(string const& _fpath, int _sz, SDL_Renderer* _ren);

    Texture_obj textures[FONT_ATLAS_TX_ARR_LEN];
};

#endif //#ifndef FONT_ATLAS_HPP
