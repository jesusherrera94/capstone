#ifndef SLOWDOWN_H
#define SLOWDOWN_H

#include "SDL.h"
#include "power_up.h"
#include "snake.h"
#include <iostream>

class SlowDown : public PowerUp {
public:

    void ApplyEffect(Snake &snake) override {
        snake.speed -= 0.05;
    }

    void Render(SDL_Renderer *renderer) override {
        SDL_Rect block{position.x * 32, position.y * 32, 32, 32};
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF); // Blue color
        SDL_RenderFillRect(renderer, &block);
    }
};

#endif // SLOWDOWN_H