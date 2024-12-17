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

    void Render(SDL_Renderer *renderer) override {
        std::cout << "Rendering speed booster" << std::endl;
        SDL_Rect block{position.x * 32, position.y * 32, 32, 32};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red color
        SDL_RenderFillRect(renderer, &block);
    }
};

#endif // SPEEDBOOSTER_H
