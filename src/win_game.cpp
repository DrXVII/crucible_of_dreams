#include "win_game.hpp" //header of this implementation file
//TODO change the name of this file

#include "Tilemap.hpp"
#include "utils.hpp"
#include "Level.hpp"
#include "Viewport.hpp"

int run_game(SDL_Renderer* _ren, const int _win_w, const int _win_h,
        Asset_container* _assets)
{
    //init game
    Timer loop_timer;
    int tgt_fps {61};
    unsigned sec_frame_count {0}; //how many frames we actually did so far this second
    unsigned fact_fps {0}; //how many frames we actually did over the last second
    long ns_this_sec {0}; //how many ns have passed this second
    std::chrono::nanoseconds tgt_frm_len = std::chrono::nanoseconds{SEC_NS} / tgt_fps;
    std::chrono::nanoseconds frm_delta {0}; //how long the frame took to execute
    bool show_fps {false};
    bool cap_fps {true};
    SDL_Point fps_xy {20, 20};
    char fps_str_buf[12] {0};

    //hardcoding map tile/cell size while we don't have a level file format
    constexpr size_t tile_w = 32;
    constexpr size_t tile_h = 16;

    cru::Level level(20, 20, tile_w, tile_h);
    level.load_test_assets(_ren);
    level.load_test_level();
    cru::Viewport viewport(&level);
    //TODO window dimensions shoud be in a program_environment struct/class
    viewport.set_screen_pos(cru::Rect{_win_w /2, 0, _win_w, _win_h});

    //main loop
    bool flag_quit {false};
    while(flag_quit == false) {
        loop_timer.start();

        ns_this_sec += frm_delta.count(); //adding length of last frame for averaging

        SDL_SetRenderDrawColor(_ren, 0x00, 0x00, 0x00, 0x00);
        
        //input and update phase
        SDL_Event event;
        const Uint8* key_states = SDL_GetKeyboardState(NULL);
        //key down/up check
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN) {
                if(key_states[SDL_SCANCODE_F]) { show_fps = !show_fps; }
                if(key_states[SDL_SCANCODE_Q]) { flag_quit = true; }
                if(key_states[SDL_SCANCODE_U]) {
                    if(cap_fps) {dbg(9, "uncapping fps\n");}
                    else {dbg(9, "capping fps\n");}
                    cap_fps = !cap_fps;
                }
                else if(key_states[SDL_SCANCODE_COMMA]) {/*TODO tile change*/ }
                else if(key_states[SDL_SCANCODE_PERIOD]) {/*TODO tile change*/ }
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                int x,y;
                SDL_GetMouseState(&x, &y);
                dbgf(0, "mousedown at %d/%d\n", x, y);
            }
            else if(event.type == SDL_QUIT) {flag_quit = true;}
        }

        //render phase
        SDL_RenderClear(_ren);

        viewport.render(_ren);

        if(show_fps) {
            if(ns_this_sec >= SEC_NS) {
                ns_this_sec -= SEC_NS;
                fact_fps = sec_frame_count - 1;
                sec_frame_count = 1;
            }

            int len =
                snprintf(fps_str_buf, sizeof fps_str_buf, "FPS: %u", fact_fps);
            _assets->get_font(0)->nprint(fps_str_buf, &fps_xy, len, _ren);
        }

        if(flag_quit == true) { break; }

        SDL_RenderPresent(_ren);

        //limit framerate
        if(cap_fps) {
            frm_delta = loop_timer.get_dur();

            if(frm_delta < tgt_frm_len) {
                std::chrono::nanoseconds wait_len = tgt_frm_len - frm_delta;

                std::this_thread::sleep_for(wait_len);
            }
        }

        ++sec_frame_count;

        //final length of the frame (after frame-cap procedure if any, etc)
        frm_delta = loop_timer.get_dur();
    }

    return 0;
}
