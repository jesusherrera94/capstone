#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>
#include <vector>
#include <SDL.h>

class ScoreManager {
public:
    ScoreManager();
    ~ScoreManager();
    void RequestPlayerName(const int score);
    void SaveScore(const std::string& playerName, int score);
    void DisplayScores(SDL_Window* window, SDL_Renderer* renderer);

private:
    std::vector<std::pair<std::string, int>> scores;
    std::string GetPlayerName();
};

#endif
