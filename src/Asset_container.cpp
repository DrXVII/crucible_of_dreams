#include "Asset_container.hpp" //header for this implementation file

Asset_container::~Asset_container()
{
    this->unload();
}



SDL_Texture* Asset_container::get_tx(unsigned _pos)
{
    if(_pos < this->txs.size()) {return this->txs[_pos];}
    //TODO try to return some default texture e.g. '?' before resorting to null
    else {return nullptr;}
}

Font_atlas* Asset_container::get_font(unsigned _pos)
{
    if(_pos < this->fonts.size()) {return this->fonts[_pos];}
    //TODO try to return some default font before resorting to null
    else {return nullptr;}
}

int Asset_container::load_fonts(SDL_Renderer* _ren, vector<string>* _paths)
{
    //TODO incorporate font sizes into parameters of function
    int sz = 12;

    for(size_t i = 0; i < _paths->size(); ++i) { 
        this->fonts.push_back(nullptr);
        this->fonts.back() = new Font_atlas((*_paths)[i], sz, _ren);
        if(this->fonts.back() == nullptr) {
            dbgf(0, "unable to load font \"%s\"\n", (*_paths)[i].c_str());
            return 1;}
    }


    return 0;
}

int Asset_container::load_textures(SDL_Renderer* _ren, vector<string>* _paths)
{
    if(_ren == nullptr || _paths == nullptr)  {
        errlog(ERRLOG_GEN, "texture loading not successfull.");
        return -1;
    }

    for(size_t i = 0; i < _paths->size(); ++i) {
        dbgf(0, "loading texture: %s\n", (*_paths)[i].c_str());
        this->txs.push_back(load_texture((*_paths)[i], _ren));
    }

    return 0;
}

void Asset_container::unload()
{
    this->unload_textures();
    this->unload_fonts();
}

void Asset_container::unload_textures()
{
    for(size_t i = 0; i < this->txs.size(); ++i) {
        dbgf(0, "unloading texture %u\n", i);

        SDL_ClearError();
        SDL_DestroyTexture(this->txs[i]);

        if(strlen(SDL_GetError()) != 0) {
            errlog(ERRLOG_SDL, "could not destroy texture!");
        }
        else { this->txs[i] = nullptr; }
    }

    this->txs.clear();
    this->txs.shrink_to_fit();
}

void Asset_container::unload_fonts()
{
    for(size_t i = 0; i < this->fonts.size(); ++i) {
        delete this->fonts[i];
        this->fonts[i] = nullptr;
    }

    this->fonts.clear();
    this->fonts.shrink_to_fit();
}
