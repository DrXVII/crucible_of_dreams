#include "win_game.hpp" //header of this implementation file
//TODO change the name of this file

#include "Tilemap.hpp"
#include "utils.hpp"

struct tmp_tiles {
    Tile selected;
    Tile cobble;
    Tile wall;
};

void load_lvl(Tilemap* tilemap, tmp_tiles* tiles);

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
    struct tmp_tiles tiles {
        //.cobble = Tile(_assets->get_tx(TX_FLOOR_COBBLE)),
        //.wall = Tile(_assets->get_tx(TX_WALL))
        .selected = Tile(load_texture("data/gfx/tiles/tile_selected.png", _ren)),
        .cobble = Tile(load_texture("data/gfx/tiles/floor_cobble.png", _ren)),
        .wall =  Tile(load_texture("data/gfx/tiles/floor_wall.png", _ren))
    };
    //using the tile object to represent player graphically (placeholder solution)
    Tile player(_assets->get_tx(TX_PLAYER));

    //TODO temporary solution (brought here to use in move key input processing)
    int tile_hw = 16;
    SDL_Point player_xy{5*tile_hw, 5*tile_hw};

    Tilemap tilemap(20, 20);
    load_lvl(&tilemap, &tiles);

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
                //TODO use less-than and greater-than (shift-comma, shift-period)
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

        //TODO window dimensions shoud be in a program_environment struct/class
        tilemap.render(320, 0, _win_w, _win_h, _ren);

        tilemap.highlight_mouseover(_ren, &tiles.selected);

        player.render(_ren, &player_xy);

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

void load_lvl(Tilemap* tilemap, tmp_tiles* tiles)
{
    for(size_t x = 0; x < tilemap->get_w(); ++x) {
        for(size_t y = 0; y < tilemap->get_h(); ++y) {
            tilemap->put_tile(&tiles->cobble, x, y);
        }
    }

    //making a square room
    SDL_Rect room_rect{10, 3, 3, 5};
    for(int x {0}; x < room_rect.w; ++x) {
        for(int y {0}; y < room_rect.h; ++y) {
            if(x == 0 || x == room_rect.w - 1
            || y == 0 || y == room_rect.h - 1) {
                tilemap->put_tile(&tiles->wall,
                        room_rect.x + x, room_rect.y + y);
            }
        }
    }
}
