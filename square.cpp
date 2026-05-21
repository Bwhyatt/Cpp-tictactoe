//
// Created by brand on 10/05/2026.
//
#include "square.h"
#include <iostream>
#include <ostream>

square::square(int givenx, int giveny, int givenw, int givenh, float dirgiven, float speedgiven)
    : x(givenx), y(giveny), w(givenw), h(givenh),  dir(dirgiven) ,speed(speedgiven){}
void square::draw(SDL_Renderer* renderer) const {
    // Set the color for drawing (e.g., White)
    SDL_SetRenderDrawColor(renderer, 100, 255, 255, 255);
    const SDL_Rect rect = {x, y, w, h};
    // Draw the actual shape or texture
    SDL_RenderFillRect(renderer, &rect);
}
bool square::Collision( square square2) const
{
  if (x + w /*+ speed * blah*/>= square2.x && x + w <= square2.x + square2.w
  || square2.x + square2.w >= x && square2.x + square2.w <= x + w)
  {
        return true;
  }
    return false;
}
bool square::HitWall(SDL_Window* window) const {
    if (x + w >= SDL_GetWindowSurface(window)->w || x <= 0) {
        return true;//not finished yet
    }
    return false;
}
void square::move( float takendir, float takenspeed, float deltatime)
{
    x += static_cast<int>(takendir * deltatime * takenspeed);
}