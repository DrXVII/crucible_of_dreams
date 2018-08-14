#ifndef FONT_ATLAS_HPP
#define FONT_ATLAS_HPP

//c++ std lib
#include <string>
using std::string;

//c std lib
#include <string.h>

//homebrew
#include "Texture_obj.hpp"
#include "utils.hpp"
#include "dbg.h"

//there are 95 printable characters in the ASCII table (positions 32-126)
#define FONT_ATLAS_TX_ARR_START 32
#define FONT_ATLAS_TX_ARR_END 126
#define FONT_ATLAS_TX_ARR_LEN (FONT_ATLAS_TX_ARR_END-FONT_ATLAS_TX_ARR_START +1)

class Font_atlas {
public:
    Font_atlas(string const& _fpath, int _sz, SDL_Renderer* _ren);
    ~Font_atlas();

    //TODO printing functions should not be a part of this class
    //render text with _ren
    int print(const char* _txt, int _x, int _y, SDL_Renderer* _ren);
    int print(const char* _txt, SDL_Point* _xy, SDL_Renderer* _ren);
    int nprint(const char* _txt, SDL_Point* _xy, int _txt_len,
        SDL_Renderer* _ren);

    int get_h();
    int get_w();

#ifdef DEBUG
    void show_atlas(SDL_Renderer* _ren);
#endif //#ifdef DEBUG

private:
    int fill(string const& _fpath, int _sz, SDL_Renderer* _ren);

    int glyph_w;
    int glyph_h;
    SDL_Texture* atlas;
};

#endif //#ifndef FONT_ATLAS_HPP
