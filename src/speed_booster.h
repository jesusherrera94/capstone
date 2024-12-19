#ifndef SPEEDBOOSTER_H
#define SPEEDBOOSTER_H

#include "SDL.h"
#include "power_up.h"
#include "snake.h"
#include <iostream>

class SpeedBooster : public PowerUp {
public:
    void ApplyEffect(Snake &snake) override {
        snake.speed += 0.05;
    }

    void Render(SDL_Renderer *renderer, SDL_Rect block) override {
        block.x = position.x * block.w;
        block.y = position.y * block.h;
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red color
        SDL_RenderFillRect(renderer, &block);
    }
};

#endif // SPEEDBOOSTER_H
