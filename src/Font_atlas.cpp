#include "Font_atlas.hpp" //header for this implementation file

Font_atlas::Font_atlas(string const& _fpath, int _sz, SDL_Renderer* _ren)
{
    if(this->fill(_fpath, _sz, _ren) != 0) {
        //TODO print fpath
        dbg("failed to fill font atlas");
    }
}

Font_atlas::~Font_atlas()
{
    //TODO destroy the textures in Texture_obj array "textures"
    for(unsigned i = 0; i < FONT_ATLAS_TX_ARR_LEN; ++i) {
        SDL_DestroyTexture(this->textures[i].tx);
        this->textures[i].w = 0;
        this->textures[i].h = 0;
    }
}

int Font_atlas::fill(string const& _fpath, int _sz, SDL_Renderer* _ren)
{
    /* will use white for now, could then just modify color on render later
     * when needed */
    SDL_Colour col = {0xFF, 0xFF, 0xFF, 0xFF};
    for(unsigned i = 0; i < FONT_ATLAS_TX_ARR_LEN; ++i) {
        this->textures[i] = Texture_obj {nullptr, 0, 0};

        char txt_buf[2] = "?"; // translates to "?\0" when compiling
        txt_buf[0] = FONT_ATLAS_TX_ARR_START + i;
        this->textures[i].tx = txt_to_tx(txt_buf, _sz, col,
                _fpath.c_str(), _ren);

        if(this->textures[i].tx == nullptr) { return -1; }

        SDL_QueryTexture(this->textures[i].tx, NULL, NULL,
                &this->textures[i].w, &this->textures[i].h);

        if(this->textures[i].w == 0 || this->textures[i].h == 0) {
            //TODO handle error - at least print somthing to dbg
            return -1;
        }

        dbgf("making txt tx_map char '%s', w = %d, h = %d\n", txt_buf,
                this->textures[i].w, this->textures[i].h);
    }

    return 0;
}

int Font_atlas::print(string const& _txt, SDL_Point* _xy,
        SDL_Renderer* _ren)
{
    SDL_Rect rect {_xy->x, _xy->y, 0, 0};
    //get the correct texture and render
    for(size_t i = 0; i < _txt.size(); ++i) {
        rect.w = this->textures[_txt[i] - FONT_ATLAS_TX_ARR_START].w;
        rect.h = this->textures[_txt[i] - FONT_ATLAS_TX_ARR_START].h;

        SDL_RenderCopy(_ren,
                this->textures[_txt[i] - FONT_ATLAS_TX_ARR_START].tx,
                NULL, &rect);

        //TODO handle error

        rect.x += rect.w;
    }

    return 0;
}

#ifdef DEBUG
void Font_atlas::test(SDL_Renderer* _ren)
{
    SDL_Rect rect {0, 0, 0, 0};

    for(unsigned i = 0; i < FONT_ATLAS_TX_ARR_LEN; ++i) {
        rect.w = this->textures[i].w;
        rect.h = this->textures[i].h;

        SDL_RenderCopy(_ren, this->textures[i].tx, NULL, &rect);

        rect.x += this->textures[i].w;
        if(rect.x >= 600) {
            rect.x = 20;
            rect.y += this->textures[i].h;
        }
    }
}
#endif //#ifdef DEBUG
