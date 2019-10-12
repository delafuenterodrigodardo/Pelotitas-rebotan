#ifndef BOUNCYBALL_H_INCLUDED
#define BOUNCYBALL_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL_Image.h"

class BouncyBall{

public:
    void setTexture(SDL_Texture *tex);
    void draw(SDL_Renderer *rende);
    void update();
    void setPos(float x, float y);



private:
    SDL_Texture *texture=nullptr;
    float x=0;
    float y=0;
    float dy=0;
    const float gravity= -0.02;


};

#endif // BOUNCYBALL_H_INCLUDED
