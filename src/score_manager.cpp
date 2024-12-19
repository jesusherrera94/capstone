#include "score_manager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utils.h"

ScoreManager::ScoreManager() {
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
    DisplayScores();
}

void ScoreManager::SaveScore(const std::string& playerName, int score) {
    std::ofstream file("scores.txt", std::ios::app);
    if (file.is_open()) {
        file << playerName << " " << score << std::endl;
        file.close();
    }
}

void ScoreManager::LoadScores() {
    std::ifstream file("scores.txt", std::ios::in);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::string playerName;
            int score;
            std::istringstream iss(line);
            iss >> playerName >> score;
            scores.push_back(std::make_pair(playerName, score));
        }
        file.close();
    }
}


void ScoreManager::renderMultilineText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color, int maxWidth) {
    auto lines = Utils::splitIntoLines(text, maxWidth, font);
    int yOffset = y;

    for (const auto& line : lines) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, line.c_str(), color);
        if (!textSurface) {
            std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
            continue;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(textSurface);
            continue;
        }

        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        SDL_FreeSurface(textSurface);

        SDL_Rect renderQuad = { x, yOffset, textWidth, textHeight };
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
        SDL_DestroyTexture(textTexture);

        yOffset += textHeight + 5;
    }
}


void ScoreManager::DisplayScores() {
    LoadScores();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Window* window = SDL_CreateWindow("Top Scores", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return;
    }

    char* basePath = SDL_GetBasePath();
    std::string fontPath = std::string(basePath) + "assets/font.ttf";
    SDL_free(basePath);
    std::string pathToFonts = Utils::removeWordFromString(fontPath, "build/");

    TTF_Font* font = TTF_OpenFont(pathToFonts.c_str(), 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return;
    }

    // Sort scores in descending order
    std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return b.second < a.second;
    });

    int yOffset = 50;
    SDL_Color textColor = {255, 255, 255, 255};
    std::string scoreText = "Top Scores: \n";
    for (size_t i = 0; i < scores.size() && i < 10; ++i) {
        scoreText += std::to_string((i+1))+") "+scores[i].first + ": " + std::to_string(scores[i].second) + "\n";
    }
    scoreText += "\nPress Enter to continue...";
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_TEXTINPUT) {
                continue;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    quit = true;
                } else if (e.key.keysym.sym == SDLK_BACKSPACE ) {
                    continue;
                } 
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderMultilineText(renderer, font, scoreText, 50, 50, textColor, 540);
        SDL_RenderPresent(renderer);
    }
    

    


    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
   
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

    return playerName;
}