/*
 * This file should contain various utility functions that are too few in their
 * own class to merit a separate header file. Naturally - many will hang around
 * here until they are grouped as more functions get created.
 * */

#ifndef UTILS_HPP
#define UTILS_HPP

//c++ std lib
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cerr;

//third party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//homebrew
#include "dbg.h"

enum {
    TX_PLAYER = 0,
    TX_FLOOR_COBBLE,
    TX_BUTTON,
    TX_BUTTON_PRESSED,
    TX_WALL
};

//generate an SDL_Texture from a string
SDL_Texture* txt_to_tx(const char* _txt, int _sz, SDL_Colour _col,
                      const char* _fpath, SDL_Renderer* _ren);
SDL_Surface* load_surface(string const& _fpath);
SDL_Texture* load_texture(string const& _fpath, SDL_Renderer* _ren);

/*TODO temporary placeholder while there is not a config file
 * textures and the like should be loaded
 * dynamically from config files (e.g. a level file). */
int make_txpaths(vector<string>* fpath_arr_);

#endif //define UTILS_HPP
