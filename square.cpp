//
// Created by brand on 10/05/2026.
//

#include "square.h"
#include <iostream>
#include <cmath>

square::square(
    int idgiven,
    Vec2 givenPosition,
    Vec2 givenSize,
    Vec2 givenVelocity,
    float givenMass,
    SDL_Color givenColour
)
    : id(idgiven),
      position(givenPosition),
      size(givenSize),
      velocity(givenVelocity),
      force(0, 0),
      momentum(0, 0),
      mass(givenMass),
      color(givenColour)
{
}

void square::draw(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(
        renderer,
        color.r,
        color.g,
        color.b,
        color.a
    );

    const SDL_Rect rect = {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    };

    SDL_RenderFillRect(renderer, &rect);
}

auto square::CalculateLinearMomentumX(
    const Vec2& velocity2,
    float mass2
) -> std::array<Vec2, 2>
{
    float newVelocity1X =
        velocity.x * (mass - mass2) / (mass + mass2)
        + velocity2.x * (2 * mass2) / (mass + mass2);

    float newVelocity2X =
        velocity.x * (2 * mass) / (mass + mass2)
        + velocity2.x * (mass2 - mass) / (mass + mass2);

    Vec2 newVelocity1(newVelocity1X, velocity.y);
    Vec2 newVelocity2(newVelocity2X, velocity2.y);

    return {newVelocity1, newVelocity2};
}

int square::CollisionY(const square& square2) const
{
    if(
        position.y + size.y >= square2.position.y &&
        position.y + size.y <= square2.position.y + square2.size.y &&
        std::abs(position.x - square2.position.x) <= position.x + size.x
    )
    {
        return 1;
    }

    if(
        square2.position.y + square2.size.y >= position.y &&
        square2.position.y + square2.size.y <= position.y + size.y &&
        std::abs(position.x - square2.position.x)
            <= square2.position.x + square2.size.x
    )
    {
        return -1;
    }

    return 0;
}

int square::CollisionX(square& square2)
{
    if(
        position.y < square2.position.y + square2.size.y &&
        position.y + size.y > square2.position.y
    )
    {
        if(
            position.x + size.x >= square2.position.x &&
            position.x + size.x <= square2.position.x + square2.size.x &&
            std::abs(position.y - square2.position.y) <= position.y + size.y
        )
        {
            if(square2.id != id)
            {
                return 1;
            }
        }

        if(
            square2.position.x + square2.size.x >= position.x &&
            square2.position.x + square2.size.x <= position.x + size.x &&
            std::abs(position.y - square2.position.y)
                <= square2.position.y + square2.size.y
        )
        {
            if(square2.id != id)
            {
                return -1;
            }
        }
    }

    return 0;
}

Vec2 square::Fnet(const std::vector<Vec2>& forces)
{
    Vec2 sum(0, 0);

    for(const Vec2& currentForce : forces)
    {
        sum += currentForce;
    }

    return sum;
}

int square::HitWall(SDL_Window* window) const
{
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    if(
        position.x + size.x >= windowSurface->w ||
        position.x <= 0
    )
    {
        return -1;
    }

    if(
        position.y + size.y >= windowSurface->h ||
        position.y <= 0
    )
    {
        return 1;
    }

    return 0;
}

void square::move(float deltatime)
{
    position += velocity * deltatime;
    momentum = velocity * mass;
}