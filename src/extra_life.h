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

    void Render(SDL_Renderer *renderer, SDL_Rect block) override {
        block.x = position.x * block.w;
        block.y = position.y * block.h;
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // green color
        SDL_RenderFillRect(renderer, &block);
    }

private:
    LivesManager &livesManager;
};

#endif // EXTRALIFE_H
