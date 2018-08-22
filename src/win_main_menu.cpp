#include "win_main_menu.hpp"

#define MAIN_MENU_QUIT 1

struct Win_env {
    int state;
};

//TODO there should be a struct/class for more environment parameters (like main window resolution, windowed mode, etc), and should be initialised earlier - maybe in main()
struct Game_env {
    SDL_Renderer* ren;
    Asset_container* assets;
};

void btnf_quit(void* _data) {
    ((Win_env*)_data)->state = MAIN_MENU_QUIT;
}

void btnf_run(void* _data) {
    Game_env* env = (Game_env*) _data;
    //TODO after moving run_game() call to main_menu() from main(), game suffered about 30fps drop; (do the extra loaded objects i.e. buttons somehow affect this? what is causing this?)
    run_game(env->ren, 800, 640, env->assets);
}

int main_menu(SDL_Renderer* _ren, Asset_container* _assets)
{
    Win_env win_env { .state = 0 };
    Game_env game_env { .ren = _ren, .assets = _assets };

    int btn_y {30};
    vector<Button*> btn_arr;
    btn_arr.push_back(new Button("epic button", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50));
    btn_arr.push_back(new Button("button 2 nop", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50));
    btn_arr.push_back(new Button("button 3 nop", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50));
    btn_arr.push_back(new Button("button 4 nop", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50));
    btn_arr.push_back(new Button("quit", _assets->get_font(0),
            _assets->get_tx(2), _assets->get_tx(3), 290, btn_y += 50));

    btn_arr[0]->set_on_rel(btnf_run);
    btn_arr[4]->set_on_rel(btnf_quit);

    //btn_arr[0].set_on_click();
    //btn_arr[0].set_on_rel();

    while (win_env.state != MAIN_MENU_QUIT) {
        SDL_SetRenderDrawColor(_ren, 0x00, 0x00, 0x00, 0x00);
        
        //*** input phase ***
        SDL_Event event;
        //key down/up check
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN) {
                const Uint8* key_states = SDL_GetKeyboardState(NULL);
                //if(key_states[SDL_SCANCODE_F]) {show_fps = !show_fps;}
                if(key_states[SDL_SCANCODE_Q]) {win_env.state = MAIN_MENU_QUIT;}
                //if(key_states[SDL_SCANCODE_U]) {cap_fps = !cap_fps;}
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                for(size_t i = 0; i < btn_arr.size(); ++i) {
                    btn_arr[i]->click((void*) &win_env);
                }
            }
            else if(event.type == SDL_MOUSEBUTTONUP) {
                for(size_t i = 0; i < btn_arr.size(); ++i) {
                    //TODO very temporary solution
                    if(i == 0) {btn_arr[i]->unclick((void*) &game_env);}
                    else {btn_arr[i]->unclick((void*) &win_env);}
                }
            }
            else if(event.type == SDL_QUIT) {win_env.state = MAIN_MENU_QUIT;}
        }

        //*** render phase ***
        SDL_RenderClear(_ren);

        //tst_btn.render(_ren);
        for(size_t i = 0; i < btn_arr.size(); ++i) {btn_arr[i]->render(_ren);}

        //finalizing render phase
        SDL_RenderPresent(_ren);
    }

    //deinit
    for(size_t i = 0; i < btn_arr.size(); ++i) {delete btn_arr[i];}

    return 0;
}
