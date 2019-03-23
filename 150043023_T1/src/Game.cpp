#include <iostream>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "Game.h"

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
  if (instance != nullptr)
    exit(-1); // TODO: HANDLE THIS ERROR

  instance = this;

  // SDL initialization
  int sdl_initialization_error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  if (sdl_initialization_error) {
    printf("%s\n", SDL_GetError()); // FIXME: Move this to a helper
    exit(-1);
  }

  // SDL_image initialization
  int IMG_FLAGS = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF); // TODO: Turn into constant?
  int sdl_image = IMG_Init(IMG_FLAGS);

  if (sdl_image != IMG_FLAGS) {
    printf("%s\n", SDL_GetError());
    exit(-1);
  }

  // SDL_mixer initialization
  int MIX_FLAGS = MIX_INIT_OGG; // TODO: Turn into constant?
  int sdl_mix = Mix_Init(MIX_FLAGS);

  if(sdl_mix != MIX_FLAGS) {
    printf("%s\n", SDL_GetError());
    exit(-1);
  }

  int DEFAULT_CHUNKSIZE = 1024;
  int mix_open = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                               MIX_DEFAULT_CHANNELS, DEFAULT_CHUNKSIZE);
  if (mix_open) {
    printf("%s\n", SDL_GetError());
    exit(-1);
  }

  // Window creation
  window = SDL_Window *SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (window == nullptr) {
    printf("%s\n", SDL_GetError());
    exit(-1);
  }
                               
  // Renderer creation
  int SUPPORTED_RENDERER = -1;
  renderer = SDL_Renderer * SDL_CreateRenderer(window, SUPPORTED_RENDERER, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    printf("%s\n", SDL_GetError());
    exit(-1);
  }

  state = new State(); // TODO: Check this
}

Game::~Game(){
  if (state != nullptr)
	  delete stored_state;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  Mix_Quit();
  Mix_CloseAudio();
  IMG_Quit();
  SDL_Quit();
}

void Game::Run() {
  while (not state.quitRequested) {
    state.Update();
    state.Render();
    SDL_RenderPresent();
    SDL_Delay(33); // TODO: Remove magic number (it is in milliseconds)
  }
}

State& Game::GetState() {
  return *state;
}

SDL_Renderer* Game::GetRenderer() {
  return renderer;
}

Game &Game::GetInstance()
{
  if (instance == nullptr)
    instance = new Game();

  return *instance;
}