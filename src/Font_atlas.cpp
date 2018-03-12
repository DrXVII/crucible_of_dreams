#include "Font_atlas.hpp" //header for this implementation file

Font_atlas::Font_atlas(string const& _fpath, int _sz, SDL_Renderer* _ren)
{
    if(this->fill(_fpath, _sz, _ren) != 0) {
        errlogf(ERRLOG_GEN, "failed to fill font atlas from '%s'.",
                _fpath.c_str());
    }
}

Font_atlas::~Font_atlas()
{
    dbg(9, "font atlas unloading glyphs\n");

    for(unsigned i = 0; i < FONT_ATLAS_TX_ARR_LEN; ++i) {
        dbgf(10, "font atlas unloading glyph %u\n", i);

        this->glyphs[i].w = 0;
        this->glyphs[i].h = 0;

        SDL_ClearError();
        SDL_DestroyTexture(this->glyphs[i].tx);
        if(strlen(SDL_GetError()) != 0) {
            errlog(ERRLOG_SDL,
                    "failed to free texture while destroying font_atlas.");
        }
        else { this->glyphs[i].tx = nullptr; }
    }
}

int Font_atlas::fill(string const& _fpath, int _sz, SDL_Renderer* _ren)
{
    /* will use white for now, could then just modify color on render later
     * when needed */
    SDL_Colour col = {0xFF, 0xFF, 0xFF, 0xFF};
    for(unsigned i = 0; i < FONT_ATLAS_TX_ARR_LEN; ++i) {
        this->glyphs[i] = Texture_obj {nullptr, 0, 0};

        char txt_buf[2] = "?"; // translates to "?\0" when compiling
        txt_buf[0] = FONT_ATLAS_TX_ARR_START + i;
        this->glyphs[i].tx = txt_to_tx(txt_buf, _sz, col,
                _fpath.c_str(), _ren);

        if(this->glyphs[i].tx == nullptr) {
            errlog(ERRLOG_GEN, "font_atlas glyph loading error.");
            return -1;
        }

        SDL_QueryTexture(this->glyphs[i].tx, NULL, NULL,
                &this->glyphs[i].w, &this->glyphs[i].h);

        if(this->glyphs[i].w == 0 || this->glyphs[i].h == 0) {
            errlog(ERRLOG_GEN, "font atlas glyph w or h == 0 !");
            return -1;
        }

        dbgf(10, "making font_atlas glyph for '%s', w = %d, h = %d\n", txt_buf,
                this->glyphs[i].w, this->glyphs[i].h);
    }

    return 0;
}

int Font_atlas::print(const char* _txt, SDL_Point* _xy, SDL_Renderer* _ren)
{
    SDL_Rect rect {_xy->x, _xy->y, 0, 0};
    size_t txt_len = strlen(_txt);

    //get the correct texture and render
    for(size_t i = 0; i < txt_len; ++i) {
        rect.w = this->glyphs[_txt[i] - FONT_ATLAS_TX_ARR_START].w;
        rect.h = this->glyphs[_txt[i] - FONT_ATLAS_TX_ARR_START].h;

        int rc = SDL_RenderCopy(_ren,
                 this->glyphs[_txt[i] - FONT_ATLAS_TX_ARR_START].tx,
                 NULL, &rect);
        if(rc != 0) {
            errlog(ERRLOG_SDL, "could not render font_atlas glyph.");
        }

        rect.x += rect.w;
    }

    return 0;
}

int Font_atlas::nprint(const char* _txt, SDL_Point* _xy, int _txt_len,
        SDL_Renderer* _ren)
{
    SDL_Rect rect {_xy->x, _xy->y, 0, 0};

    //get the correct texture and render
    for(int i = 0; i < _txt_len; ++i) {
        rect.w = this->glyphs[_txt[i] - FONT_ATLAS_TX_ARR_START].w;
        rect.h = this->glyphs[_txt[i] - FONT_ATLAS_TX_ARR_START].h;

        int rc = SDL_RenderCopy(_ren,
                 this->glyphs[_txt[i] - FONT_ATLAS_TX_ARR_START].tx,
                 NULL, &rect);
        if(rc != 0) {
            errlog(ERRLOG_SDL, "could not render font_atlas glyph.");
        }

        rect.x += rect.w;
    }

    return 0;
}

#ifdef DEBUG
void Font_atlas::test(SDL_Renderer* _ren)
{
    SDL_Rect rect {0, 0, 0, 0};

    for(unsigned i = 0; i < FONT_ATLAS_TX_ARR_LEN; ++i) {
        rect.w = this->glyphs[i].w;
        rect.h = this->glyphs[i].h;

        SDL_RenderCopy(_ren, this->glyphs[i].tx, NULL, &rect);

        rect.x += this->glyphs[i].w;
        if(rect.x >= 600) {
            rect.x = 20;
            rect.y += this->glyphs[i].h;
        }
    }
}
#endif //#ifdef DEBUG
