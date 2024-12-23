#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include "SDL.h"

#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "score_manager.h"
#include "livesManager.h"
#include "power_up.h"
#include "state_manager.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, StateManager &stateManager);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration, ScoreManager &scoreManager);
  int GetScore() const;
  int GetSize() const;

 private:
  std::unique_ptr<Snake> snake;
  SDL_Point food;
  std::unique_ptr<LivesManager> livesManager;
  std::vector<std::shared_ptr<PowerUp>> powerUps;
  std::mutex powerUpsMutex;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  StateManager &stateManager;

  int score{0};

  void PlaceFood();
  void Update();
  void initializeSnake(std::size_t grid_width, std::size_t grid_height);
  void PlacePowerUp();
  void PowerUpThread();
};

#endif