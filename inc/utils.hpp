/*
 * This file should contain various utility functions that are too few in their
 * own class to merit a separate header file. Naturally - many will hang around
 * here until they are grouped as more functions get created.
 * */

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

//generate an SDL_Texture from a string
SDL_Texture* txt_to_tx(const char* _txt, int _sz, SDL_Colour _col,
                      const char* _fpath, SDL_Renderer* _ren);
SDL_Surface* load_surface(string const& _fpath);
SDL_Texture* load_texture(string const& _fpath, SDL_Renderer* _ren);

int load_textures(SDL_Renderer* _ren,
        vector<SDL_Texture*>* _tx_arr, vector<string>* _fpath_arr);
void unload_textures(vector<SDL_Texture*>* _arr);

/*TODO temporary placeholder while there is not a config file
 * textures and the like should be loaded
 * dynamically from config files (e.g. a level file). */
int make_txpaths(vector<string>* fpath_arr_);
