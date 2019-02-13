#include "win_game.hpp" //header of this implementation file

#include "Tilemap.hpp"

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
    Tile cobble(_assets->get_tx(1));
    Tile wall(_assets->get_tx(4));
    //using the tile object to represent player graphically (placeholder solution)
    Tile player(_assets->get_tx(0));

    //TODO temporary solution (brought here to use in move key input processing)
    int tile_hw = 16;
    SDL_Point player_xy{5*tile_hw, 5*tile_hw};

    Tilemap tiles(20, 20);
    for(size_t x = 0; x < tiles.get_w(); ++x) {
        for(size_t y = 0; y < tiles.get_h(); ++y) {
            tiles.put_tile(&cobble, x, y);
        }
    }

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
                if(key_states[SDL_SCANCODE_UP])    { player_xy.y -= tile_hw; }
                else if(key_states[SDL_SCANCODE_DOWN])  { player_xy.y += tile_hw; }
                else if(key_states[SDL_SCANCODE_LEFT])  { player_xy.x -= tile_hw; }
                else if(key_states[SDL_SCANCODE_RIGHT]) { player_xy.x += tile_hw; }
            }
            else if(event.type == SDL_QUIT) {flag_quit = true;}
        }

        //render phase
        SDL_RenderClear(_ren);

        //TODO window dimensions shoud be in a program_environment struct/class
        tiles.render(0, 0, _win_w, _win_h, _ren);

        //TODO just a placeholer
        //
        //temporary solution to tilemap rendering
        ////int start_x = 0;
        ////int start_y = 0;
        ////SDL_Point ren_pt{start_x, start_y};
        ////for(unsigned i = 1000; i > 0; --i) {

        ////    cobble.render(_ren, &ren_pt);
        ////    ren_pt.x += tile_hw;

        ////    if(ren_pt.x >= _win_w) {
        ////        ren_pt.x = start_x;
        ////        ren_pt.y += tile_hw;
        ////    }

        ////    if(ren_pt.y >= _win_h) { break; }
        ////}

        //////putting in a square room
        ////SDL_Rect room_rect{10 * tile_hw, 3 * tile_hw, 3, 5};
        ////for(int x {0}; x < room_rect.w; ++x) {
        ////    for(int y {0}; y < room_rect.h; ++y) {
        ////        if(x == 0 || x == room_rect.w - 1 || y == 0 || y == room_rect.h - 1) {
        ////            ren_pt = {room_rect.x + x * tile_hw, room_rect.y + y * tile_hw};
        ////            wall.render(_ren, &ren_pt);
        ////        }
        ////    }
        ////}

        player.render(_ren, &player_xy);
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
