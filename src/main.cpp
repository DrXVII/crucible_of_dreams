//cpp std lib
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::to_string;
#include <memory>
using std::shared_ptr;
#include <cmath>
using std::sin;
using std::cos;
using std::acos;
#include <chrono>
#include <thread>

//3rd party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//homebrew
#include "Timer.hpp"
#include "utils.hpp"
#include "Tile.hpp"

#define SEC_NS 1000000000 /* one second expressed in nanoseconds int literal */
//TODO default font paths should be set differently, preferably from cfg files
#define DEF_MONO_FONT_PATH "data/fonts/terminus/TerminusTTF-4.46.0.ttf"

const int win_w = 800;
const int win_h = 640;
const string win_title = "Crucible of Dreams";

int init(); //initialise SDL
int create_main_win(SDL_Window*& _win,
                    string const& _title, const int _w, const int _h);
int create_win_renderer(SDL_Window* _win, SDL_Renderer*& _ren);
void close(SDL_Window*& _win, SDL_Renderer*& _ren);
//void run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h);
void run_game(SDL_Renderer* _ren);

int main()
{
    if(init() != 0) {
        cerr << "the application will now exit.\n";
        return 1;
    }
    
    SDL_Window* win_main = NULL;
    SDL_Renderer* ren_main = NULL;
    
    if(create_main_win(win_main, win_title, win_w, win_h) != 0) {
        close(win_main, ren_main);
        return 1;
    }
    
    if(create_win_renderer(win_main, ren_main) != 0) {
        close(win_main, ren_main);
        return 1;
    }

    //run_game(ren_main, win_w, win_h);
    run_game(ren_main);
    
    close(win_main, ren_main);
    return 0;
}

int init()
{
    /*TODO make a logger to handle error reporting.
     * Implement some specific options for SDL, IMG and TTF as the second line
     * in similar messages is allways the same. */
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "ERROR: FATAL - could not initialise SDL! "
             << "SDL error = " << SDL_GetError() << "\n";
        return -1;
    }
    
    int sdl_image_flags = IMG_INIT_PNG;
    if(!(IMG_Init(sdl_image_flags) & sdl_image_flags)) {
        cerr << "ERROR: FATAL - could not initialise SDL_image! "
             << "SDL_image error = " << IMG_GetError() << "\n";
        return -1;
    }

    if(TTF_Init() == -1) {
        cerr << "ERROR: FATAL - could not initialise SDL_ttf! "
             << "SDL_ttf error = " << TTF_GetError() << "\n";
        return -1;
    }
    
    return 0;
}

int create_main_win(SDL_Window*& _win,
        const string& _title, const int _w, const int _h)
{
    _win = SDL_CreateWindow(_title.c_str(),
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            _w, _h,
                             SDL_WINDOW_SHOWN);
    if(_win == NULL) {
        cerr << "ERROR: FATAL - SDL window could not be created!\n";
        cerr << "SDL error = " << SDL_GetError() << "\n";
        return 1;
    }
    
    return 0;
}

int create_win_renderer(SDL_Window* _win, SDL_Renderer*& _ren)
{
    _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
    
    if(_ren == NULL) {
        cerr << "ERROR: Could not create renderer!\n";
        cerr << "SDL error = " << SDL_GetError() << "\n";
        return 1;
    }
    
    //initialise renderer colour
    SDL_SetRenderDrawColor(_ren, 0xff, 0xff, 0xff, 0xff);
    
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

//void run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h)
void run_game(SDL_Renderer* _ren)
{
    //init game
    Timer loop_timer;
    int tgt_fps {60};
    std::chrono::nanoseconds tgt_frm_len = std::chrono::nanoseconds{SEC_NS} / tgt_fps;
    std::chrono::nanoseconds frm_delta {0}; //how long the frame took to execute
    bool show_fps {false};
    bool cap_fps {true};

    vector<SDL_Texture*> tx_arr = load_textures(_ren);
    if(tx_arr.size() < 2) { cerr << "smth wrong w tx_arr\n"; return; }

    //main loop
    bool flag_quit {false};
    while(flag_quit == false) {
        SDL_SetRenderDrawColor(_ren, 0x00, 0x00, 0x00, 0x00);
        loop_timer.start();
        
        //input and update phase
        SDL_Event event;
        const Uint8* key_states = SDL_GetKeyboardState(NULL);
        //key down/up check
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN) {
                if(key_states[SDL_SCANCODE_F]) {
                    if(show_fps) {show_fps = false;}
                    else {show_fps = true;}
                }
                if(key_states[SDL_SCANCODE_Q]) { flag_quit = true; }
                if(key_states[SDL_SCANCODE_U]) {
                    if(tgt_fps < 10000) {
                        tgt_fps = 10000;
                        tgt_frm_len =
                            std::chrono::nanoseconds{SEC_NS} / tgt_fps;
                    }
                    else {
                        tgt_fps = 60;
                        tgt_frm_len =
                            std::chrono::nanoseconds{SEC_NS} / tgt_fps;
                    }
                }
            }
            else if(event.type == SDL_QUIT) {flag_quit = true;}
        }

        //TODO ASAP (redo) just a placeholer
        SDL_Texture* fps_tx = nullptr;
        Tile border(tx_arr[0]);
        Tile cobble(tx_arr[1]);
        //--placeholder------------------------------------------------------

        if(show_fps) {
            /*TODO (speed) use more efficient text rendering (when implemented)
             * this brought potential FPS from 10k to 300 */
            //TODO?(speed) think of a more efficient way to get the number
            fps_tx = txt_to_tx("FPS: " + to_string(SEC_NS / frm_delta.count()),
                    12, SDL_Colour{0x00, 0x00, 0xFF, 0x00},
                    DEF_MONO_FONT_PATH, _ren);
        }

        //render phase
        SDL_RenderClear(_ren);

        SDL_Point ren_pt{50, 50};
        border.render(_ren, &ren_pt);
        ren_pt.y += 20;
        cobble.render(_ren, &ren_pt);

        if(show_fps) {
            //TODO ASAP (redo) just a placeholer, think of how to implement textured objects the best
            int w = 100, h = 100;
            if(SDL_QueryTexture(fps_tx, NULL, NULL, &w, &h)) {
                cerr << "SDL_QueryTexture ERROR: " << SDL_GetError() << "\n";
            }
            SDL_Rect fps_tx_rect {20, 20, w*2, h*2};
            //--placeholder------------------------------------------------------

            SDL_RenderCopy(_ren, fps_tx, NULL, &fps_tx_rect);
        }

        if(flag_quit == true) {
            break;
        }

        SDL_RenderPresent(_ren);

        //limit framerate
        frm_delta = loop_timer.get_dur();
        if(cap_fps && frm_delta < tgt_frm_len) {
            std::chrono::nanoseconds wait_len = tgt_frm_len - frm_delta;
            if(wait_len > std::chrono::nanoseconds{0}) {
                //SDL_Delay(wait_len);
                std::this_thread::sleep_for(wait_len);
                //TODO move to dbg.cpp
                //DBG
                fprintf(stderr,
                        "tgt: %lfs delta: %lfs wait: %lfs possible_fps: %ld\n",
                        (1.0 * tgt_frm_len.count()) / SEC_NS,
                        (1.0 * frm_delta.count()) / SEC_NS,
                        (1.0 * wait_len.count()) / SEC_NS,
                        SEC_NS / frm_delta.count());
                frm_delta += wait_len;
            }
        }

        //TODO
        //final length of the frame (after frame-cap procedure if any, etc)
        //frm_delta = loop_timer.get_dur();
    }

    unload_textures(&tx_arr);
}
