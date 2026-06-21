#include <iostream>
#include <list>
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
    square obj(1, 500, 400, 100, 100, -1, 300, 00, 1, 100,  SDL_Color(255, 100, 100, 0));
    square obj2(2, 100, 400, 100, 100, 1, 100, 00, 1,100, SDL_Color(100, 200, 100, 0));
    std::vector<square*> myVec = {&obj, &obj2};
    bool flag = false;
    //return value of x collision
    std::list<int> listt1 = {0, 1, 2};
    while (running) {
        current_time = SDL_GetTicks();
        // delta_time in seconds
        delta_time = static_cast<float>(current_time - last_time)/1000.0f;
        last_time = current_time;
        myVec = {&obj, &obj2};
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
        int ReturncolX = obj.CollisionX(obj2);
        int returncolY = obj.CollisionY(obj2);
        //std::cout << (abs(obj2.x - obj.x) < obj.w ?  "should be colliding" : "Not colliding" )<< std::endl;
        if ( returncolY != 0) {
            //std::cout << "Collision y" <<std::endl;
        }
        if (ReturncolX != 0 ) {
           // std::cout << "Collision x" <<std::endl;
        }
        /*if (ReturncolX != 0 ) {
            obj.dirx *= -1.0;
            obj2.dirx *= -1.0;
            std::cout << "Collision x" <<std::endl;
        }
        if ( returncolY != 0) {
            obj.diry *= -1.0;
            obj2.diry *= -1.0;
            std::cout << "Collision y" <<std::endl;
        }*/
        for (int i = 0; i < myVec.size(); i++) {
            if (myVec[i]->HitWall(window) == -1) {
                myVec[i]->x = myVec[i]->x + myVec[i]->w>= SDL_GetWindowSurface(window)->w  ? SDL_GetWindowSurface(window)->w -myVec[i]->w - 1 : 1;
                //need to handle logic if it's colliding with something
                myVec[i]->dirx *= -1.0;
            }
            /*if (myVec[i]->HitWall(window) == 1) {
                myVec[i]->y = myVec[i]->diry > 0 ? SDL_GetWindowSurface(window)->h -myVec[i]->h - 1 : 1;
                myVec[i]->diry *= -1.0;
                std::cout << "Wall hit at y position" << myVec[i] ->y << std::endl;
            }*/


            for (int j = 0; j < myVec.size(); j++) {//std::cout << "My vec 0 lastobj is " << myVec[0]->Lastobj << "myvec j id is " << myVec[1]->id<< std::endl;
                 int Xcol = myVec[i]->CollisionX(*myVec[j]);
                if (Xcol != 0 && i != j && myVec[i]->Lastobj != myVec[j]->id)
                {
                    if (abs(myVec[i]->x - myVec[j]->x) > abs(myVec[i]->y - myVec[j]->y)) {
                        //problem is directions keep getting changed

                        auto result = myVec[i]->CalculateLinearMomentumX(myVec[j]->velx, myVec[j]->mass, myVec[i]->dirx);

                        myVec[i]->velx = result[1];
                        myVec[i]->dirx = result[1] < 0 ? -1:1;
                        myVec[j]->velx = result[0];
                        myVec[j]->dirx = result[0] < 0 ? -1:1;
                        if (myVec[i]-> x > myVec[j]->x) {
                            myVec[i]->x = myVec[j]->x + myVec[j]->w;

                        }
                        if (myVec[i]->x < myVec[j]->x) {
                            myVec[j]->x = myVec[i]->x + myVec[i]->w;
                        }
                        std::cout << "myVec[i] velx is" << myVec[i]->velx * myVec[i]->dirx<< std::endl;
                        std::cout << "myVec[j] velx is" << myVec[j]->velx * myVec[j]->dirx<< std::endl;
                        std::erase(myVec, myVec[1]); //this will not work in future

                    }

                    std::cout << "difference in x " << abs(myVec[i]->x - myVec[j]->x) << "difference in y" <<  abs(myVec[i]->y - myVec[j]->y) <<std::endl;
                }
            }
        }
        obj.move(obj.dirx,obj.diry, obj.velx,obj.vely, delta_time);
        obj2.move(obj2.dirx,obj2.diry, obj2.velx, obj2.vely, delta_time);
        SDL_SetRenderDrawColor(renderer, 200, 20, 40, 255);
        obj.draw(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 200, 40, 255);
        obj2.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}