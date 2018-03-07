#include "utils.hpp" // header for this implementation file

SDL_Texture* txt_to_tx(string const& _txt, int _sz, SDL_Colour _col,
                      string const& _fpath, SDL_Renderer* _ren)
{
    TTF_Font* ft = TTF_OpenFont(_fpath.c_str(), _sz);
    if(ft == nullptr) {
        cerr << "ERROR: could not load font! "
             << "SDL_ttf error = " << TTF_GetError() << "\n";
        return nullptr;
    }

    SDL_Surface* surf = TTF_RenderText_Solid(ft, _txt.c_str(), _col);
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
        cerr << "ERROR: could not load surface from '" << _fpath << "'."
             << "SDL_img error = " << IMG_GetError() << "\n";
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

vector<SDL_Texture*> load_textures(SDL_Renderer* _ren)
{
    vector<SDL_Texture*> tx_arr;

    /*TODO temporarily hardcoded, textures and the like should be loaded
     * dynamically from config files (e.g. a level file) */
    tx_arr.push_back(load_texture("data/gfx/tiles/floor_border.png", _ren));
    tx_arr.push_back(load_texture("data/gfx/tiles/floor_cobble.png", _ren));

    return tx_arr;
}

void unload_textures(vector<SDL_Texture*>* _arr)
{
    for(unsigned i = 0; i < _arr->size(); ++i) {
        SDL_DestroyTexture((*_arr)[i]);
        (*_arr)[i] = nullptr;
    }
}
