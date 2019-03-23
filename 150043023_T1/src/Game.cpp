#include <iostream>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "Game.h"

Game &Game::GetInstance()
{
  if (instance == nullptr)
    instance = new Game();

  return *instance;
}