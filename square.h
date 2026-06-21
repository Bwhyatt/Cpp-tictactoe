//
// Created by brand on 10/05/2026.
//

#ifndef HI_SQUARE_H
#define HI_SQUARE_H
#include <vector>
#include <SDL2/SDL_render.h>
#include <array>

class square {
private:

public:
    int x, y, w, h;
    float dirx, diry;
    float force;
    float mass;
    SDL_Color color;
    float velx, vely;

    float momentumx, momentumy;
    int Lastobj = -1;
    int id;
    //SDL_Surface * renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    square(int id, int givenx, int giveny, int givenw, int givenh, float dirxgiven,
    float speedgiven, float speedygiven, float dirygiven, float mass, SDL_Color colorgiven);
    void draw(SDL_Renderer* renderer) const;
    auto CalculateLinearMomentumX(float u2, float m2, float dir2) -> std::array<float, 2>;
    void move( float takendir, float takendiry, float takenspeed, float takenspeedy, float deltatime) ;
    int CollisionX( square square2) ;
    int CollisionY( square square2) const;
    static int FnetX(const std::vector<std::array<float, 3>>& v) ;
    int HitWall(SDL_Window* window) const;

};



#endif //HI_SQUARE_H
