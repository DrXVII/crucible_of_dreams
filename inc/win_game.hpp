#ifndef WIN_GAME_HPP
#define WIN_GAME_HPP

//cpp std lib
#include <thread>

//3rd party libs
#include <SDL2/SDL.h>

//homebrew
#include "Asset_container.hpp"
#include "Timer.hpp"
#include "Tile.hpp"

#define SEC_NS 1000000000 /* one second expressed in nanoseconds int literal */

int run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h,
        Asset_container* _assets);

#endif //define WIN_GAME_HPP
