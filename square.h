//
// Created by brand on 10/05/2026.
//

#ifndef HI_SQUARE_H
#define HI_SQUARE_H

#include <array>
#include <vector>
#include <SDL2/SDL.h>
#include "Vec2.h"

class square {
private:

public:
    Vec2 position;
    Vec2 size;
    Vec2 velocity;
    Vec2 force;
    Vec2 momentum;

    float mass;
    SDL_Color color;

    int Lastobj = -1;
    int id;

    square(
        int id,
        Vec2 givenPosition,
        Vec2 givenSize,
        Vec2 givenVelocity,
        float mass,
        SDL_Color colorgiven
    );

    void draw(SDL_Renderer* renderer) const;

    auto CalculateLinearMomentumX(
        const Vec2& velocity2,
        float mass2
    ) -> std::array<Vec2, 2>;

    void move(float deltatime);

    int CollisionX(square& square2);

    int CollisionY(const square& square2) const;

    static Vec2 Fnet(const std::vector<Vec2>& forces);

    int HitWall(SDL_Window* window) const;
};

#endif //HI_SQUARE_H