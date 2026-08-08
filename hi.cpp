#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <SDL2/SDL.h>
#include "square.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "My Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    bool running = true;
    SDL_Event event;

    Uint64 last_time = SDL_GetPerformanceCounter();

    double frequency =
        static_cast<double>(SDL_GetPerformanceFrequency());

    const double fixedDt = 1.0 / 60.0;
    double accumulator = 0.0;

    square obj(
        1,
        Vec2(500, 400),
        Vec2(100, 100),
        Vec2(-300, 0),
        100,
        SDL_Color{255, 100, 100, 255}
    );

    square obj2(
        2,
        Vec2(100, 400),
        Vec2(100, 100),
        Vec2(100, 0),
        100,
        SDL_Color{100, 200, 100, 255}
    );

    std::vector<square*> myVec = {&obj, &obj2};

    bool flag = false;
    std::list<int> listt1 = {0, 1, 2};
    int counter = 0;

    while(running)
    {
        Uint64 current_time = SDL_GetPerformanceCounter();

        double frameTime =
            (current_time - last_time) / frequency;

        last_time = current_time;

        myVec = {&obj, &obj2};

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }

            if(
                event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE
            )
            {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);

        accumulator += frameTime;

        while(accumulator >= fixedDt)
        {
            accumulator -= fixedDt;

            int ReturncolX = obj.CollisionX(obj2);
            int returncolY = obj.CollisionY(obj2);

            if(returncolY != 0)
            {
            }

            if(ReturncolX != 0)
            {
            }

            for(int i = 0; i < myVec.size(); i++)
            {
                if(myVec[i]->HitWall(window) == -1)
                {
                    SDL_Surface* windowSurface =
                        SDL_GetWindowSurface(window);

                    myVec[i]->position.x =
                        myVec[i]->position.x + myVec[i]->size.x
                            >= windowSurface->w
                        ? windowSurface->w - myVec[i]->size.x - 1
                        : 1;

                    myVec[i]->velocity.x *= -1.0f;
                }

                for(int j = i + 1; j < myVec.size(); j++)
                {
                    int Xcol =
                        myVec[i]->CollisionX(*myVec[j]);

                    if(Xcol != 0 && i != j)
                    {
                        if(
                            std::abs(
                                myVec[i]->position.x -
                                myVec[j]->position.x
                            )
                            >
                            std::abs(
                                myVec[i]->position.y -
                                myVec[j]->position.y
                            )
                        )
                        {
                            Vec2 relativeVelocity =
                                myVec[j]->velocity -
                                myVec[i]->velocity;

                            Vec2 normal =
                                myVec[j]->position.x >
                                myVec[i]->position.x
                                ? Vec2(1, 0)
                                : Vec2(-1, 0);

                            float velocityAlongNormal =
                                relativeVelocity.Dot(normal);

                            if(velocityAlongNormal < 0)
                            {
                                auto result =
                                    myVec[i]->CalculateLinearMomentumX(
                                        myVec[j]->velocity,
                                        myVec[j]->mass
                                    );

                                myVec[i]->velocity = result[0];
                                myVec[j]->velocity = result[1];
                            }

                            if(
                                myVec[i]->position.x >
                                myVec[j]->position.x
                            )
                            {
                                myVec[i]->position.x =
                                    myVec[j]->position.x +
                                    myVec[j]->size.x;
                            }

                            if(
                                myVec[i]->position.x <
                                myVec[j]->position.x
                            )
                            {
                                myVec[j]->position.x =
                                    myVec[i]->position.x +
                                    myVec[i]->size.x;
                            }

                            std::cout
                                << "myVec[i] velocity.x is "
                                << myVec[i]->velocity.x
                                << std::endl;

                            std::cout
                                << "myVec[j] velocity.x is "
                                << myVec[j]->velocity.x
                                << std::endl;

                            counter++;
                        }

                        std::cout
                            << "iteration "
                            << counter
                            << std::endl;
                    }
                }
            }

            obj.move(fixedDt);
            obj2.move(fixedDt);
        }

        obj.draw(renderer);
        obj2.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}