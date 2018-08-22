#include "win_game.hpp" //headef of this implementation file

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
    char fps_str_buf[12];

    //TODO just a placeholer
    Tile border(_assets->get_tx(0));
    Tile cobble(_assets->get_tx(1));

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
                if(key_states[SDL_SCANCODE_U]) { cap_fps = !cap_fps; }
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
        //--end-placeholder-----------------------------------------------------

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
