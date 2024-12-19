#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"
#include "livesManager.h"
#include "power_up.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, std::vector<std::shared_ptr<PowerUp>> const &powerUps);
  void UpdateWindowTitle(int score, int fps, LivesManager const &livesManager);
  SDL_Window *GetWindow() const { return sdl_window; }
  SDL_Renderer *GetRenderer() const { return sdl_renderer; }

  std::size_t GetScreenWidth() const { return screen_width; }
  std::size_t GetScreenHeight() const { return screen_height; }
  std::size_t GetGridWidth() const { return grid_width; }
  std::size_t GetGridHeight() const { return grid_height; }

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif