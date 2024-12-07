#include "score_manager.h"
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utils.h"

ScoreManager::ScoreManager() {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
    }
}

ScoreManager::~ScoreManager() {
    TTF_Quit();
}

void ScoreManager::RequestPlayerName(const int score) {
    std::string playerName = Utils::removeWordFromString(GetPlayerName(), "Player Name:");
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

std::string ScoreManager::GetPlayerName() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return "Player";
    }

    SDL_Window* window = SDL_CreateWindow("Enter Player Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return "Player";
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return "Player";
    }
    char* basePath = SDL_GetBasePath();
    std::string fontPath = std::string(basePath) + "assets/font.ttf";
    SDL_free(basePath);
    std::string pathToFonts = Utils::removeWordFromString(fontPath, "build/");

    TTF_Font* font = TTF_OpenFont(pathToFonts.c_str(), 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return "Player";
    }

    

    SDL_StartTextInput();
    std::string playerName = "Player Name:";
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_TEXTINPUT) {
                playerName += e.text.text;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    quit = true;
                } else if (e.key.keysym.sym == SDLK_BACKSPACE && playerName.length() > 0 && playerName.length() >= 13) {
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

        SDL_Rect renderQuad = { (640 - textWidth) / 2, (480 - textHeight) / 2, textWidth, textHeight };
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
        SDL_DestroyTexture(textTexture);
        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // SDL_Quit();

    return playerName;
}