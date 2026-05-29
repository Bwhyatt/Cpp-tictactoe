//
// Created by brand on 10/05/2026.
//
#include "square.h"
#include <iostream>
#include <ostream>

square::square(int givenx, int giveny, int givenw, int givenh, float dirxgiven, float speedgiven, float dirygiven, float speedygiven)
    : x(givenx), y(giveny), w(givenw), h(givenh),  dirx(dirxgiven) ,diry(dirygiven), speedx(speedgiven), speedy(speedygiven){}
void square::draw(SDL_Renderer* renderer) const {
    // Set the color for drawing (e.g., White)
    SDL_SetRenderDrawColor(renderer, 100, 255, 255, 255);
    const SDL_Rect rect = {x, y, w, h};
    // Draw the actual shape or texture
    SDL_RenderFillRect(renderer, &rect);
}
int square::Collision( square square2) const
{
  if ((x + w /*+ speed * blah*/>= square2.x && x + w <= square2.x + square2.w && y +h >= square2.y && y <= square2.h + square2.y)
  || square2.x + square2.w >= x && square2.x + square2.w <= x + w && y + h>= square2.y && y <= square2.h + square2.y)
  {
        return -1;//this works for now if we are only going to reverse direction
  }
  /*if (y + h >= square2.y && y + h <= square2.y + square2.h || square2.y + square2.h >= y && square2.y + square2.h <= y + h) {

    return 1;
  }*/
    return 0;
}
int square::HitWall(SDL_Window* window) const {
    if (x + w >= SDL_GetWindowSurface(window)->w || x <= 0) {
        return -1;//-1 is x
    }
    if (y + h >= SDL_GetWindowSurface(window)->h || y <= 0) {
        return 1;
    }
    return false;
}
void square::move( float takendir, float takendiry, float takenspeed, float takenspeedy, float deltatime)
{
    x += static_cast<int>(takendir * deltatime * takenspeed);
    y += static_cast<int>(takendiry * deltatime * takenspeedy);
}