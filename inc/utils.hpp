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

//generate an SDL_Texture from a string
SDL_Texture* txt_to_tx(string const& _txt, int _sz, SDL_Colour _col,
                      string const& _fpath, SDL_Renderer* _ren);
SDL_Surface* load_surface(string const& _fpath);
SDL_Texture* load_texture(string const& _fpath, SDL_Renderer* _ren);

//TODO should be moved to specialised header/src file(s) along with other functions used to initialise stages (start, levels, etc.) of the program
vector<SDL_Texture*> load_textures(SDL_Renderer* _ren);
void unload_textures(vector<SDL_Texture*>* _arr);
