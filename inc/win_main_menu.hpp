#ifndef WIN_MAIN_MENU_HPP
#define WIN_MAIN_MENU_HPP

//cpp std lib
#include <vector>
using std::vector;

//3rd party libs
#include <SDL2/SDL.h>

//homebrew
#include "dbg.h"
#include "version.h"
#include "win_game.hpp"
#include "Font_atlas.hpp"
#include "Button.hpp"
#include "Asset_container.hpp"

int main_menu(SDL_Renderer* _ren, Asset_container* _assets);

#endif //define WIN_MAIN_MENU_HPP
