//
// Created by brand on 10/05/2026.
//
#include "square.h"
#include <iostream>
#include <ostream>

square::square(int givenx, int giveny, int givenw, int givenh, float dirgiven)
    : x(givenx), y(giveny), w(givenw), h(givenh),  dir(dirgiven) {}
void square::draw(SDL_Renderer* renderer) const {
    // Set the color for drawing (e.g., White)
    SDL_SetRenderDrawColor(renderer, 100, 255, 255, 255);
    const SDL_Rect rect = {x, y, w, h};
    // Draw the actual shape or texture
    SDL_RenderFillRect(renderer, &rect);
    std::cout << "X is " << x << std::endl;
}
void square::move( float takendir, int takenspeed, float deltatime)  {
    x += static_cast<int>(takendir * deltatime * static_cast<float>(takenspeed));
}