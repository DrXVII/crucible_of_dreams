#include "Font_atlas.hpp" //header for this implementation file

Font_atlas::Font_atlas(string const& _fpath, int _sz, SDL_Renderer* _ren)
: glyph_w(0)
, glyph_h(0)
, atlas(nullptr)
{
    if(this->fill(_fpath, _sz, _ren) != 0) {
        errlogf(ERRLOG_GEN, "failed to fill font atlas from '%s'.",
                _fpath.c_str());
    }
}

Font_atlas::~Font_atlas()
{
    if(this->atlas != nullptr) {
        SDL_DestroyTexture(this->atlas);
        //TODO error handling
        this->atlas = nullptr;
    }
}

int Font_atlas::fill(string const& _fpath, int _sz, SDL_Renderer* _ren)
{
    /* will use white for now, could then just modify color on render later
     * when needed */
    SDL_Colour clr = {0xFF, 0xFF, 0xFF, 0xFF};

    //get dimensions of one glyph
    SDL_Texture* glyph = txt_to_tx("a", _sz, clr, _fpath.c_str(), _ren);
    SDL_QueryTexture(glyph, NULL, NULL, &this->glyph_w, &this->glyph_h);
    SDL_DestroyTexture(glyph);
    glyph = nullptr;

    //painting the texture atlas
    dbgf(9, "painting font texture atlas from %s\n", _fpath.c_str());
    int atlas_w = this->glyph_w * FONT_ATLAS_TX_ARR_LEN;
    int atlas_h = this->glyph_h;
    this->atlas = SDL_CreateTexture(
            _ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
            atlas_w, atlas_h);

    SDL_SetRenderTarget(_ren, this->atlas);
    SDL_Rect dst_rect { .x = 0, .y = 0,
                        .w = this->glyph_w, .h = this->glyph_h};

    for(unsigned i = 0; i < FONT_ATLAS_TX_ARR_LEN; ++i) {
        char txt_buf[2] = "?"; // translates to "?\0" when compiling
        txt_buf[0] = FONT_ATLAS_TX_ARR_START + i;
        glyph = txt_to_tx(txt_buf, _sz, clr, _fpath.c_str(), _ren);

        if(glyph == nullptr) {
            errlog(ERRLOG_GEN, "font_atlas glyph loading error.");
            return -1;
        }

        int tx_w = 0;
        int tx_h = 0;
        SDL_QueryTexture(glyph, NULL, NULL, &tx_w, &tx_h);

        if(tx_w == 0 || tx_h == 0) {
            errlog(ERRLOG_GEN, "font atlas glyph w or h == 0 !");
            return -1;
        }

        dbgf(10, "made font_atlas glyph for '%s', w = %d, h = %d\n", txt_buf,
                tx_w, tx_h);

        dst_rect.x = dst_rect.w * i;
        SDL_RenderCopy(_ren, glyph, NULL, &dst_rect);
        dbgf(10, "painted glyph %u(%c)\n", i, i + FONT_ATLAS_TX_ARR_START);

        SDL_DestroyTexture(glyph);
        glyph = nullptr;
    }

    //reset to default render target
    SDL_SetRenderTarget(_ren, NULL);

    return 0;
}

int Font_atlas::print(const char* _txt, int _x, int _y, SDL_Renderer* _ren)
{
    SDL_Point pt{_x, _y};
    return this->print(_txt, &pt, _ren);
}

int Font_atlas::print(const char* _txt, SDL_Point* _xy, SDL_Renderer* _ren)
{
    size_t txt_len = strlen(_txt);

    return this->nprint(_txt, _xy, txt_len, _ren);
}

int Font_atlas::nprint(const char* _txt, int _x, int _y, int _txt_len,
        SDL_Renderer* _ren)
{
    SDL_Point pt{_x, _y};
    return this->nprint(_txt, &pt, _txt_len, _ren);
}

int Font_atlas::nprint(const char* _txt, SDL_Point* _xy, int _txt_len,
        SDL_Renderer* _ren)
{

    SDL_Rect dst_rect { .x = _xy->x, .y = _xy->y,
        .w = this->glyph_w, .h = this->glyph_h };
    SDL_Rect src_rect { .x = 0, .y = 0, .w = dst_rect.w, .h = dst_rect.h };

    for(int i = 0; i < _txt_len; ++i) {
        src_rect.x = src_rect.w * (_txt[i] - FONT_ATLAS_TX_ARR_START);

        SDL_RenderCopy(_ren, this->atlas, &src_rect, &dst_rect);
        dst_rect.x += src_rect.w;
    }

    return 0;
}

int Font_atlas::get_h() { return this->glyph_h; }
int Font_atlas::get_w() { return this->glyph_w; }

#ifdef DEBUG
void Font_atlas::show_atlas(SDL_Renderer* _ren)
{
    SDL_Rect dst_rect { .x = 0, .y = 0,
                        .w = this->glyph_w * FONT_ATLAS_TX_ARR_LEN,
                        .h = this->glyph_h};
    SDL_RenderCopy(_ren, this->atlas, NULL, &dst_rect);
}
#endif //#ifdef DEBUG
