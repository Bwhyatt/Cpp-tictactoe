//
// Created by brand on 10/05/2026.
//

#ifndef HI_SQUARE_H
#define HI_SQUARE_H
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class square {
private:

public:
    int x, y, w, h;
    float dirx, diry;
    float speedx, speedy;
    //SDL_Surface * renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    square(int givenx, int giveny, int givenw, int givenh, float dirxgiven, float speedgiven, float speedygiven, float dirygiven);
    void draw(SDL_Renderer* renderer) const;

    void move( float takendir, float takendiry, float takenspeed, float takenspeedy, float deltatime) ;
    int Collision( square square2) const;
    int HitWall(SDL_Window* window) const;

};



#endif //HI_SQUARE_H
