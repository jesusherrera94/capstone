#include <iostream>
#include "SDL.h"

#include "game.h"
#include "speed_booster.h"
#include "slow_down.h"
#include "extra_life.h"

const int INITIAL_LIVES = 3;

Game::Game(std::size_t grid_width, std::size_t grid_height, StateManager &stateManager)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      livesManager(std::make_unique<LivesManager>(INITIAL_LIVES)),
      stateManager(stateManager) {
        initializeSnake(grid_width, grid_height);
        PlaceFood();
        PlacePowerUp();
        std::thread(&Game::PowerUpThread, this).detach();
}

void Game::initializeSnake(std::size_t grid_width, std::size_t grid_height) {
  snake = std::make_unique<Snake>(grid_width, grid_height, *livesManager);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration, ScoreManager &scoreManager) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool nameHasBeenCalled = false;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, *snake, stateManager);
    if (stateManager.GetState() == StateManager::GameState::RUNNING) { 
      Update();
      if (!nameHasBeenCalled && !snake->alive) {
        nameHasBeenCalled = true;
        scoreManager.RequestPlayerName(score);
      }
      renderer.Render(*snake, food, powerUps);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, *livesManager);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}


void Game::PowerUpThread() {
    std::uniform_int_distribution<int> random_interval(5, 15); 
    while (snake->alive) {
        std::this_thread::sleep_for(std::chrono::seconds(random_interval(engine)));
        std::unique_lock<std::mutex> lk(stateManager.cv_m);
        stateManager.cv.wait(lk, [this] { return stateManager.GetState() == StateManager::GameState::RUNNING; });
        PlacePowerUp();
    }
}


void Game::PlacePowerUp() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        if (!snake->SnakeCell(x, y) && !(food.x == x && food.y == y)) {
            std::shared_ptr<PowerUp> powerUp;
            int powerUpType = rand() % 3; // 3 possibilities since there are 3 power-ups
            switch (powerUpType) {
                case 0:
                    powerUp = std::make_shared<SpeedBooster>();
                    break;
                case 1:
                    powerUp = std::make_shared<SlowDown>();
                    break;
                case 2:
                    powerUp = std::make_shared<ExtraLife>(*livesManager);
                    break;
            }
            powerUp->position = {x, y};
            {
                std::lock_guard<std::mutex> lock(powerUpsMutex);
                powerUps.push_back(powerUp);
            }
            return;
        }
    }
}

void Game::Update() {
  if (!snake->alive) { 
      stateManager.state = StateManager::GameState::GAME_OVER;
      return; 
    }

  snake->Update();

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    snake->GrowBody();
    snake->speed += 0.02;
  }

  // Check for power-up collisions
    {
        std::lock_guard<std::mutex> lock(powerUpsMutex);
        for (auto it = powerUps.begin(); it != powerUps.end();) {
            if ((*it)->position.x == new_x && (*it)->position.y == new_y) {
                (*it)->ApplyEffect(*snake);
                it = powerUps.erase(it);
            } else {
                ++it;
            }
        }
    }

}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }