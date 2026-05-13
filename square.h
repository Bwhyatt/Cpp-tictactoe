//
// Created by brand on 10/05/2026.
//

#ifndef HI_SQUARE_H
#define HI_SQUARE_H
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class square {
private:
    int x, y, w, h;
    float dir;
public:
    //SDL_Surface * renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    square(int givenx, int giveny, int givenw, int givenh, float dirgiven);
    void draw(SDL_Renderer* renderer) const;

    void move( float takendir, int takenspeed, float deltatime) ;



};



#endif //HI_SQUARE_H
