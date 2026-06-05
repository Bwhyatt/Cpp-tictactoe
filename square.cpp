//
// Created by brand on 10/05/2026.
//
#include "square.h"
#include <iostream>
#include <ostream>

square::square(int givenx, int giveny, int givenw, int givenh, float dirxgiven,
    float speedgiven, float dirygiven, float speedygiven,  float mass,SDL_Color givenColour)
    : x(givenx), y(giveny), w(givenw), h(givenh),  dirx(dirxgiven) ,diry(dirygiven),
       velx(speedgiven), vely(speedygiven), mass(mass),  color(givenColour){}
void square::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, color.a);
    const SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

int square::CollisionY(square square2) const {
    if (y + h >= square2.y && y + h <= square2.y + square2.h && abs(x - square2.x) <= x + w) {//&& x is between sqaure.x and square2.x + swuare2.w
        return 1;
    }
    if (square2.y + square2.h >= y && square2.y + square2.h <= y + h && abs(x - square2.x) <= square2.x + square2.w) {
        return -1;
    }//problem is that both will be true at the same time
    return 0;
}

int square::CollisionX( square square2) const
{/*if i have y + h this is sort of futile since to meet this condition
    there could just be a collision that is made true from the other rectangle, that would increase time complexity though*/
  if (x + w >= square2.x && x + w <= square2.x + square2.w && abs(y - square2.y) <= y + h)//magnitude of gap between
  {//this square is colliding with something on its right side
        return 1;//this works for now if we are only going to reverse direction
      //1 means that something on the right of this instance is colliding with it
  }
  if (  square2.x + square2.w >= x  && square2.x + square2.w <= x + w && abs(y - square2.y) <= square2.y + square2.h) {
    return -1;
  }
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