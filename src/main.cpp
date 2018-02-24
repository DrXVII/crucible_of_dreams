//cpp std lib
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
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

//3rd party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//homebrew
#include "Timer.h"

const int win_w = 800;
const int win_h = 640;
const string win_title = "Crucible of Dreams";

int init(); //initialise SDL
int create_main_win(SDL_Window*& _win,
                    const string& _title, const int _w, const int _h);
int create_win_renderer(SDL_Window* _win, SDL_Renderer*& _ren);
void close(SDL_Window*& _win, SDL_Renderer*& _ren);
void run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h);

int main(int argc, char* args[])
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

    run_game(ren_main, win_w, win_h);
    
    close(win_main, ren_main);
    return 0;
}

int init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "ERROR: FATAL - could not initialise SDL!\n";
        cerr << "SDL error = " << SDL_GetError() << endl;
        return -1;
    }
    
    int sdl_image_flags = IMG_INIT_PNG;
    if(!(IMG_Init(sdl_image_flags) & sdl_image_flags)) {
        cerr << "ERROR: FATAL - could not initialise SDL_image!\n";
        cerr << "SDL_image error = " << IMG_GetError() << endl;
        return -1;
    }

    if(TTF_Init() == -1) {
        cerr << "ERROR: FATAL - could not initialise SDL_ttf!\n";
        cerr << "SDL_ttf error = " << TTF_GetError() << endl;
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
        cerr << "SDL error = " << SDL_GetError() << endl;
        return 1;
    }
    
    return 0;
}

int create_win_renderer(SDL_Window* _win, SDL_Renderer*& _ren)
{
    _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
    
    if(_ren == NULL) {
        cerr << "ERROR: Could not create renderer!\n";
        cerr << "SDL error = " << SDL_GetError() << endl;
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

void run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h)
{
    //init game
    Timer loop_timer;
    const short tgt_fps = 60;
    Uint32 tgt_frame_len = 1000 / tgt_fps;
    Uint32 frame_len = 0;
    bool show_fps = false;
    SDL_Rect scene_rect = SDL_Rect{0, 0, _win_w, _win_h};

    //main loop
    bool pause = false;
    bool flag_quit = false;
    while(flag_quit == false) {
        SDL_SetRenderDrawColor(_ren, 0x00, 0x00, 0x00, 0x00);
        loop_timer.set_start(SDL_GetTicks());
        float dt = float(frame_len) / 1000.0f;
        
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
            }
            else if(event.type == SDL_QUIT) {flag_quit = true;}
        }

        if(show_fps) {
            /* TODO update the FPS text
             * req. high resolution sleep, (efficient) text rendering */
        }

        //render phase
        SDL_RenderClear(_ren);

        if(show_fps) {
            //TODO display the fps
        }

        if(flag_quit == true) {
            break;
        }

        SDL_RenderPresent(_ren);

        //limit framerate
        loop_timer.set_end(SDL_GetTicks());
        frame_len = loop_timer.get_duration();
        if(frame_len < tgt_frame_len) {
            Uint32 wait_len = tgt_frame_len - frame_len;
            if(wait_len > 0) {
                SDL_Delay(wait_len);
                frame_len += wait_len;
            }
        }
    }
}
