#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "state_manager.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, StateManager &stateManager) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  void TogglePause(StateManager &stateManager) const;
};

#endif