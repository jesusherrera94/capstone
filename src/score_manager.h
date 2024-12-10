#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>
#include <vector>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

class ScoreManager {
public:
    ScoreManager();
    ~ScoreManager();
    void RequestPlayerName(const int score);
    void SaveScore(const std::string& playerName, int score);

private:
    std::vector<std::pair<std::string, int>> scores;
    std::string GetPlayerName();
    void DisplayScores();
    void LoadScores();
    void renderMultilineText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color, int maxWidth);

};

#endif
