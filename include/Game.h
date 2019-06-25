#ifndef GAME_H
#define GAME_H
#define ASSETS_PATH "assets/"
#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.h"
#include <stack>

class Game {
private:
  static Game* instance;
  SDL_Window* window;
  SDL_Renderer* renderer;
  State* storedState;
  int frameStart;
  float dt;
  std::stack<std::unique_ptr<State>> stateStack;

  void CalculateDeltaTime();

public:
  static int screenWidth;
  static int screenHeight;

  Game(std::string title, int width, int height);
  ~Game();
  SDL_Renderer* GetRenderer();
  State& GetCurrentState();
  static Game& GetInstance();
  void Push(State *state);
  void Run();
  float GetDeltaTime();
};

#endif
