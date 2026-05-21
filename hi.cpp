#include <iostream>
#include <SDL2/SDL.h>
#include "square.h"
#include <vector>
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "My Window",          // title
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,  // position
        800,
        600,             // width, height
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // main loop
     SDL_Rect myRect = { 50, 50, 200, 150 };
    bool running = true;
    SDL_Event event;
    float dir = 1;
    Uint32 last_time = 0, current_time = 0;
    float delta_time = 0;
    int speed = 1000.0f;
    square obj(100, 100, 100, 100, 1, 200);
    square obj2(500, 100, 100, 100, -1, 200);
    std::vector<square> myVec = {&obj, &obj2};
    while (running) {
        current_time = SDL_GetTicks();
        // delta_time in seconds
        delta_time = static_cast<float>(current_time - last_time)/1000.0f;
        last_time = current_time;

        // handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) running = false;
        }
        //if (myRect.x + myRect.w > SDL_GetWindowSurface(window)->w || myRect.x < 0) dir *= -1;
        //myRect.x += static_cast<int>( delta_time* dir) * speed ;

        // clear screen (dark blue)
        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);
        //draw my obj
        if (obj.Collision(obj2)) {
            obj.dir *= -1.0;
            obj2.dir *= -1.0;
            std::cout << "Collision" <<std::endl;
        }

        for (int i = 0; i < myVec.size(); i++) {
                if (myVec[i].HitWall(window)) {
                 myVec[i].x = obj.dir > 0 ? SDL_GetWindowSurface(window)->w -myVec[i].w - 1 : 1;
                myVec[i].dir *= -1.0;
                std::cout << "JFSJEIIESIKFS" << std::endl;
            }
        }
        std::cout << obj2.dir<< std::endl;
        obj.move(obj.dir, obj.speed, delta_time);
        obj2.move(obj2.dir, obj2.speed, delta_time);
        obj.draw(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 20, 40, 255);
        obj2.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}