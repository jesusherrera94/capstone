#include "state_manager.h"

StateManager::StateManager() : state(GameState::RUNNING) {}

void StateManager::TogglePause() {
    std::unique_lock<std::mutex> lk(cv_m);
    if (state == GameState::RUNNING) {
        state = GameState::PAUSED;
    } else if (state == GameState::PAUSED) {
        state = GameState::RUNNING;
        cv.notify_all();
    }
}

StateManager::GameState StateManager::GetState() const {
    return state;
}
