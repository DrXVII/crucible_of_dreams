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
#include <thread>

//3rd party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//homebrew
#include "Timer.hpp"
#include "utils.hpp"
#include "Tile.hpp"
#include "Button.hpp"
#include "Font_atlas.hpp"

#define SEC_NS 1000000000 /* one second expressed in nanoseconds int literal */
//TODO default font paths should be set differently, preferably from cfg files
#define DEF_MONO_FONT_PATH "data/fonts/terminus/TerminusTTF-4.46.0.ttf"

const string win_title = "Crucible of Dreams";

int init(); //initialise SDL
int create_main_win(SDL_Window*& _win,
                    string const& _title, const int _w, const int _h);
int create_win_renderer(SDL_Window* _win, SDL_Renderer*& _ren);
void close(SDL_Window*& _win, SDL_Renderer*& _ren);
void run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h);

int main()
{
    if(init() != 0) {
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

    run_game(ren_main, win_w, win_h);
    
    close(win_main, ren_main);
    return 0;
}

int init()
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

void run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h)
{
    //init game
    Timer loop_timer;
    int tgt_fps {61};
    std::chrono::nanoseconds tgt_frm_len = std::chrono::nanoseconds{SEC_NS} / tgt_fps;
    std::chrono::nanoseconds frm_delta {0}; //how long the frame took to execute
    bool show_fps {false};
    bool cap_fps {true};
    SDL_Point fps_xy {20, 20};

    vector<string> tx_paths;
    make_txpaths(&tx_paths);

    vector<SDL_Texture*> tx_arr;
    if(load_textures(_ren, &tx_arr, &tx_paths) != 0) {
        errlog(ERRLOG_GEN, "texture loading not successfull.");
    }

    //no longer need to store the paths
    tx_paths.clear();
    tx_paths.shrink_to_fit();

    Font_atlas def_mono_font(DEF_MONO_FONT_PATH, 12, _ren);

    //TODO just a placeholer
    Tile border(tx_arr[0]);
    Tile cobble(tx_arr[1]);

    //TODO temporary - testing buttons - remove later
    Button tst_btn("epic button", &def_mono_font, tx_arr[2], tx_arr[3], 30, 30);

    //--end-placeholder-----------------------------------------------------

    //main loop
    bool flag_quit {false};
    while(flag_quit == false) {
        loop_timer.start();

        SDL_SetRenderDrawColor(_ren, 0x00, 0x00, 0x00, 0x00);
        
        //input and update phase
        SDL_Event event;
        const Uint8* key_states = SDL_GetKeyboardState(NULL);
        //key down/up check
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN) {
                if(key_states[SDL_SCANCODE_F]) { show_fps = !show_fps; }
                if(key_states[SDL_SCANCODE_Q]) { flag_quit = true; }
                if(key_states[SDL_SCANCODE_U]) { cap_fps = !cap_fps; }
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                if(tst_btn.check_click(mouse_x, mouse_y)) { tst_btn.press(); }
            }
            else if(event.type == SDL_MOUSEBUTTONUP) {
                tst_btn.unpress();
            }
            else if(event.type == SDL_QUIT) {flag_quit = true;}
        }

        //render phase
        SDL_RenderClear(_ren);

        //TODO just a placeholer
        //
        //temporary solution to tilemap rendering
        SDL_Point ren_pt{50, 50};
        bool offs = true;
        for(unsigned i = 400; i > 0; --i) {

            cobble.render(_ren, &ren_pt);
            //border.render(_ren, &ren_pt);
            ren_pt.x += 64;

            if(ren_pt.x >= _win_w) {
                ren_pt.x = 50;
                ren_pt.y += 16;

                if(offs) { ren_pt.x -= 32; }
                offs = !offs;
            }

            if(ren_pt.y >= _win_h) { break; }
        }
        ren_pt = SDL_Point{50, 70};
        border.render(_ren, &ren_pt);
        tst_btn.render(_ren);
        //--end-placeholder-----------------------------------------------------

        if(show_fps) {
            char buf[11];
            int len = sprintf(buf, "FPS: %ld", SEC_NS / frm_delta.count());

            def_mono_font.nprint(buf, &fps_xy, len, _ren);
        }

        if(flag_quit == true) {
            break;
        }

        SDL_RenderPresent(_ren);

        //limit framerate
        if(cap_fps) {
            frm_delta = loop_timer.get_dur();

            if(frm_delta < tgt_frm_len) {
                std::chrono::nanoseconds wait_len = tgt_frm_len - frm_delta;

                std::this_thread::sleep_for(wait_len);
            }
        }

        //final length of the frame (after frame-cap procedure if any, etc)
        frm_delta = loop_timer.get_dur();

    }

    dbg(8, "unloading general textures\n");
    unload_textures(&tx_arr);
}
