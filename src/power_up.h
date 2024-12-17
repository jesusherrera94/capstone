#ifndef POWERUP_H
#define POWERUP_H

#include "SDL.h"

class PowerUp {
public:
    virtual ~PowerUp() = default;
    virtual void ApplyEffect(Snake &snake) = 0;
    virtual void Render(SDL_Renderer *renderer) = 0;
    SDL_Point position;
    SDL_Rect block;
};

#endif // POWERUP_H
