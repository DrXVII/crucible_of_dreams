//third party libs
#include <SDL2/SDL.h>

class Tile {
public:
    Tile(SDL_Texture* _tx = nullptr, int _w = 0, int _h = 0);

    int wh_to_tx();
    void render(SDL_Renderer* _ren, SDL_Point* _pt);

private:
    int w, h;
    SDL_Texture* tx;
};
