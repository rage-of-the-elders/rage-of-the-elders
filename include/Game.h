#ifndef GAME_H
#define GAME_H
#define ASSETS_PATH "assets/"
#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.h"

class Game {
private:
  static Game* instance;
  SDL_Window* window;
  SDL_Renderer* renderer;
  State* state;
  int frameStart;
  float dt;

  Game(std::string title, int width, int height);
  void CalculateDeltaTime();

public:
  ~Game();
  void Run();
  SDL_Renderer* GetRenderer();
  State& GetState();
  static Game& GetInstance();
  float GetDeltaTime();
};

#endif