#ifndef EXTRALIFE_H
#define EXTRALIFE_H

#include "SDL.h"
#include "power_up.h"
#include "livesManager.h"
#include <iostream>

class ExtraLife : public PowerUp {
public:
    ExtraLife(LivesManager &livesManager) : livesManager(livesManager) {}

    void ApplyEffect(Snake &snake) override {
        livesManager.resetLives(livesManager.getLives() + 1);
    }

    void Render(SDL_Renderer *renderer) override {
        std::cout << "Rendering Extra life!!!" << std::endl;
        SDL_Rect block{position.x * 32, position.y * 32, 32, 32};
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // Yellow color
        SDL_RenderFillRect(renderer, &block);
    }

private:
    LivesManager &livesManager;
};

#endif // EXTRALIFE_H
