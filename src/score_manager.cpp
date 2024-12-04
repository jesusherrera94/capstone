#include "score_manager.h"
#include <iostream>
#include <fstream>
#include <SDL2/SDL_ttf.h>

ScoreManager::ScoreManager() {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
    }
}

ScoreManager::~ScoreManager() {
    TTF_Quit();
}

void ScoreManager::RequestPlayerName(SDL_Window* window, SDL_Renderer* renderer) {
    std::string playerName = GetPlayerName(window, renderer);
    int score = 0; // Replace with actual score
    SaveScore(playerName, score);
}

void ScoreManager::SaveScore(const std::string& playerName, int score) {
    scores.push_back({playerName, score});
    std::ofstream file("scores.txt", std::ios::app);
    if (file.is_open()) {
        file << playerName << " " << score << std::endl;
        file.close();
    }
}

void ScoreManager::DisplayScores(SDL_Window* window, SDL_Renderer* renderer) {
    // Implement score display logic
    
}

std::string ScoreManager::GetPlayerName(SDL_Window* window, SDL_Renderer* renderer) {
    TTF_Font* font = TTF_OpenFont("../assets/Jersey20-Regular.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return "Player";
    }

    SDL_StartTextInput();
    std::string playerName;
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_TEXTINPUT) {
                playerName += e.text.text;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    quit = true;
                } else if (e.key.keysym.sym == SDLK_BACKSPACE && playerName.length() > 0) {
                    playerName.pop_back();
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, playerName.c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        SDL_FreeSurface(textSurface);

        SDL_Rect renderQuad = { (640 - textWidth) / 2, (640 - textHeight) / 2, textWidth, textHeight };
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
        SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);

    return playerName;
}