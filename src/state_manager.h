#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <condition_variable>
#include <mutex>

class StateManager {
public:
    enum class GameState { RUNNING, PAUSED, GAME_OVER };

    StateManager();
    void TogglePause();
    GameState GetState() const;
    std::mutex cv_m;
    std::condition_variable cv;
    GameState state;
    
};

#endif // STATEMANAGER_H
