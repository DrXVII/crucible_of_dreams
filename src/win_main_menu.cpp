#include "win_main_menu.hpp"

//cpp std lib
#include <vector>
using std::vector;
#include <array>
using std::array;

//homebrew
#include "dbg.h"
#include "version.h"
#include "win_game.hpp"
#include "Font_atlas.hpp"
#include "Button.hpp"

#define MAIN_MENU_QUIT 1

struct Win_env {
    int state;
};

//TODO HIGH_PRI there should be a struct/class for more environment parameters (like main window resolution, windowed mode, etc), and should be initialised earlier - probably in main()->init_<something>()
struct Game_env {
    SDL_Renderer* ren;
    Asset_container* assets;
    /*TODO remove make_ver_str() call from main_menu()
    / char* ver_cstr; //readable string of the program version */
    Win_env* win_env; //TODO think - maybe this should just be "void* local_data" or something
    //TODO int win_w, win_h;
};

void btnf_quit(void* _data) {
    ((Game_env*)_data)->win_env->state = MAIN_MENU_QUIT;
}

void btnf_editor(void* _data) {
    Game_env* env = (Game_env*) _data;
    run_game(env->ren, 800, 640, env->assets);
}

int main_menu(SDL_Renderer* _ren, Asset_container* _assets)
{
    char ver_cstr[32];
    make_ver_str(ver_cstr, sizeof ver_cstr);

    Win_env win_env { .state = 0 };
    Game_env game_env { .ren = _ren, .assets = _assets, .win_env = &win_env };

    enum {
        BTN_EPIC = 0,
        BTN_EDITOR,
        BTN_3,
        BTN_4,
        BTN_QUIT
    };

    int btn_y {30};
    //vector<Button*> btn_arr;
    array<Button*, 5> btn_arr;
    btn_arr[BTN_EPIC]    = new Button("epic button nop", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50);
    btn_arr[BTN_EDITOR] = new Button("-e editor", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50);
    btn_arr[BTN_3]       = new Button("button 3 nop", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50);
    btn_arr[BTN_4]       = new Button("button 4 nop", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50);
    btn_arr[BTN_QUIT]    = new Button("-q quit", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50);

    //assign functions to buttons
    btn_arr[BTN_EDITOR]->set_func(btnf_editor);
    btn_arr[BTN_QUIT]->set_func(btnf_quit);

    //assign shortcuts to buttons
    btn_arr[BTN_EDITOR]->set_shortcut(SDLK_e);
    btn_arr[BTN_QUIT]->set_shortcut(SDLK_q);

    while (win_env.state != MAIN_MENU_QUIT) {
        SDL_SetRenderDrawColor(_ren, 0x00, 0x00, 0x00, 0x00);
        
        //*** input phase ***
        SDL_Event event;
        //key down/up check
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN) {
                const Uint8 key_pressed = event.key.keysym.sym;
                for(size_t i = 0; i < btn_arr.size(); ++i) {
                    btn_arr[i]->keypress(key_pressed);
                }
            }
            else if(event.type == SDL_KEYUP) {
                const auto key_unpressed = event.key.keysym.sym;
                for(size_t i = 0; i < btn_arr.size(); ++i) {
                    btn_arr[i]->keyrel(
                            key_unpressed, static_cast<void*>(&game_env));
                }
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                for(size_t i = 0; i < btn_arr.size(); ++i) {
                    btn_arr[i]->click();
                }
            }
            else if(event.type == SDL_MOUSEBUTTONUP) {
                for(size_t i = 0; i < btn_arr.size(); ++i) {
                    btn_arr[i]->unclick(static_cast<void*>(&game_env));
                }
            }
            else if(event.type == SDL_QUIT) {win_env.state = MAIN_MENU_QUIT;}
        }

        //*** render phase ***
        SDL_RenderClear(_ren);

        for(size_t i = 0; i < btn_arr.size(); ++i) {btn_arr[i]->render(_ren);}
        game_env.assets->get_font(0)->print(ver_cstr, 0, 620, _ren);

        //finalizing render phase
        SDL_RenderPresent(_ren);
    }

    //deinit
    for(size_t i = 0; i < btn_arr.size(); ++i) {delete btn_arr[i];}

    return 0;
}
