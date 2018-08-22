//cpp std lib
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
#include <cmath>
using std::sin;
using std::cos;
using std::acos;
#include <chrono>

//3rd party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//homebrew
#include "win_main_menu.hpp"
#include "win_game.hpp"
#include "Asset_container.hpp"

//TODO default font paths should be set differently, preferably from cfg files
#define DEF_MONO_FONT_PATH "data/fonts/terminus/TerminusTTF-4.46.0.ttf"

const string win_title = "Crucible of Dreams";

int init_sdl(); //initialise SDL
//initialise assets (textures, fonts, animations, etc)
int load_assets(SDL_Renderer* _ren,
        vector<SDL_Texture*>* tx_arr_, Font_atlas** font_);
void unload_assets(vector<SDL_Texture*>* _tx_arr, Font_atlas* _font);
int create_main_win(SDL_Window*& _win,
                    string const& _title, const int _w, const int _h);
int create_win_renderer(SDL_Window* _win, SDL_Renderer*& _ren);
void close(SDL_Window*& _win, SDL_Renderer*& _ren);

int main()
{
    if(init_sdl() != 0) {
        printf("the application will now exit.\n");
        return -1;
    }

    const int win_w = 800;
    const int win_h = 640;
    
    SDL_Window* win_main = NULL;
    SDL_Renderer* ren_main = NULL;
    
    if(create_main_win(win_main, win_title, win_w, win_h) != 0) {
        close(win_main, ren_main);
        return -1;
    }
    
    if(create_win_renderer(win_main, ren_main) != 0) {
        close(win_main, ren_main);
        return -1;
    }

    vector<string> paths;
    make_txpaths(&paths);

    Asset_container assets;
    assets.load_textures(ren_main, &paths);

    paths.clear();
    paths.shrink_to_fit();
    paths.push_back(DEF_MONO_FONT_PATH);

    assets.load_fonts(ren_main, &paths);

    main_menu(ren_main, &assets);
    //run_game(ren_main, win_w, win_h, &assets);
    
    assets.unload();
    close(win_main, ren_main);
    return 0;
}

int init_sdl()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        errlog(ERRLOG_SDL, "FATAL - could not initialise SDL!");
        return -1;
    }
    
    int sdl_image_flags = IMG_INIT_PNG;
    if(!(IMG_Init(sdl_image_flags) & sdl_image_flags)) {
        errlog(ERRLOG_IMG, "FATAL - could not initialise SDL_image!");
        return -1;
    }

    if(TTF_Init() == -1) {
        errlog(ERRLOG_TTF, "FATAL - could not initialise SDL_ttf!");
        return -1;
    }
    
    return 0;
}

/*TODO HIGH_PRI make one structure/function to all the game assets
 * if it will be a class - this function and friends should go there */
int load_assets(SDL_Renderer* _ren,
        vector<SDL_Texture*>* tx_arr_, Font_atlas** font_)
{
    //*** load textures ***
    vector<string> tx_paths;
    make_txpaths(&tx_paths);

    if(load_textures(_ren, tx_arr_, &tx_paths) != 0) {
        errlog(ERRLOG_GEN, "texture loading not successfull.");
    }

    //no longer need to store the paths
    tx_paths.clear();
    tx_paths.shrink_to_fit();

    //*** load fonts ***
    *font_ = nullptr;
    *font_ = new Font_atlas(DEF_MONO_FONT_PATH, 12, _ren);
    if(*font_ == nullptr) {return 1;}

    return 0;
}

void unload_assets(vector<SDL_Texture*>* _tx_arr, Font_atlas* _font)
{
    unload_textures(_tx_arr);

    delete _font;
}

int create_main_win(SDL_Window*& _win,
        const string& _title, const int _w, const int _h)
{
    _win = SDL_CreateWindow(_title.c_str(),
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            _w, _h,
                             SDL_WINDOW_SHOWN);
    if(_win == NULL) {
        errlog(ERRLOG_SDL, "FATAL - SDL window could not be created!");
        return -1;
    }
    
    return 0;
}

int create_win_renderer(SDL_Window* _win, SDL_Renderer*& _ren)
{
    _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
    
    if(_ren == NULL) {
        errlog(ERRLOG_SDL, "Could not create renderer!");
        return -1;
    }
    
    //initialise renderer colour
    SDL_SetRenderDrawColor(_ren, 0xFF, 0xFF, 0xFF, 0xFF);
    
    return 0;
}

void close(SDL_Window*& _win, SDL_Renderer*& _ren)
{
    if(_win != NULL) {SDL_DestroyWindow(_win);}
    _win = NULL;
    
    if(_ren != NULL) {SDL_DestroyRenderer(_ren);}
    _ren = NULL;
    
    SDL_Quit();
}
