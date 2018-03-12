#include "utils.hpp" // header for this implementation file

SDL_Texture* txt_to_tx(const char* _txt, int _sz, SDL_Colour _col,
                      const char* _fpath, SDL_Renderer* _ren)
{
    TTF_Font* ft = TTF_OpenFont(_fpath, _sz);
    if(ft == nullptr) {
        cerr << "ERROR: could not load font! "
             << "SDL_ttf error = " << TTF_GetError() << "\n";
        return nullptr;
    }

    SDL_Surface* surf = TTF_RenderText_Solid(ft, _txt, _col);
    if(surf == nullptr) {
        cerr << "ERROR: could not render surface from font! "
             << "SDL_ttf error = " << TTF_GetError() << "\n";

        TTF_CloseFont(ft);
        return nullptr;
    }

    SDL_Texture* tx = SDL_CreateTextureFromSurface(_ren, surf);
    if(tx == nullptr) {
        cerr << "ERROR: could not create texture from surface! "
             << "SDL error = " << SDL_GetError() << "\n";
    }

    TTF_CloseFont(ft);
    SDL_FreeSurface(surf);
    return tx;
}

SDL_Surface* load_surface(string const& _fpath)
{
    SDL_Surface* sfc = IMG_Load(_fpath.c_str());
    if(sfc == nullptr) {
        errlogf(ERRLOG_IMG, "could not load surface from %s!", _fpath.c_str());
        //cerr << "ERROR: could not load surface from '" << _fpath << "'."
        //     << "SDL_img error = " << IMG_GetError() << "\n";
        return nullptr;
    }

    return sfc;
}

SDL_Texture* load_texture(string const& _fpath, SDL_Renderer* _ren)
{
    SDL_Surface* sfc = load_surface(_fpath);
    if(sfc == nullptr) { return nullptr; }

    SDL_Texture* tx = SDL_CreateTextureFromSurface(_ren, sfc);
    SDL_FreeSurface(sfc);
    if(tx == nullptr) {
        cerr << "ERROR: could not create texture from surface " << _fpath << "."
             << "SDL error = " << SDL_GetError() << "\n";
        return nullptr;
    }

    return tx;
}

int make_txpaths(vector<string>* fpath_arr_)
{
    if(fpath_arr_ == nullptr) { return -1; }

    fpath_arr_->push_back(string{"data/gfx/tiles/floor_border.png"});
    fpath_arr_->push_back(string{"data/gfx/tiles/floor_cobble.png"});

    return 0;
}

int load_textures(SDL_Renderer* _ren,
        vector<SDL_Texture*>* _tx_arr, vector<string>* _fpath_arr)
{
    if(_ren == nullptr || _tx_arr == nullptr || _fpath_arr == nullptr) {
        return -1;
    }

    for(size_t i = 0; i < _fpath_arr->size(); ++i) {
        _tx_arr->push_back(load_texture((*_fpath_arr)[i], _ren));
    }

    return 0;
}

void unload_textures(vector<SDL_Texture*>* _arr)
{
    for(unsigned i = 0; i < _arr->size(); ++i) {
        dbgf(9, "unloading texture %u\n", i);

        SDL_ClearError();
        SDL_DestroyTexture((*_arr)[i]);

        if(strlen(SDL_GetError()) != 0) {
            errlog(ERRLOG_SDL, "could not destroy texture!");
        }
        else { (*_arr)[i] = nullptr; }
    }
}
