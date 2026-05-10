//
// Created by brand on 10/05/2026.
//

#ifndef HI_SQUARE_H
#define HI_SQUARE_H
#include <SDL2/SDL_rect.h>


class square {
public:
    float x;
    float y;
    int w;
    int h;
    SDL_surface * renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    square(float givenx, float giveny, int givenw, int givenh)
    {
        x = givenx;
        y = giveny;
        w = givenw;
        h = givenh;
    }
    void draw() {
        SDL_Rect myrect = {x, y, w, h};
        SDL_RenderFillRect(renderer, &myRect);
    }
};



#endif //HI_SQUARE_H
