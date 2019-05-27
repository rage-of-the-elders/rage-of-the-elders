#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {  
  if (instance != nullptr) {
    printf("There's already an instance of Game running!");
    exit(-1); // TODO: HANDLE THIS ERROR
  }

  instance = this;

  this->frameStart = SDL_GetTicks();
	this->dt = 0;

  // SDL initialization
  int sdl_initialization_error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  if (sdl_initialization_error) {
    printf("SDL Init Error: %s\n", SDL_GetError()); // TODO: Move this to a helper
    exit(-1);
  }

  // SDL_image initialization
  int IMG_FLAGS = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF); // TODO: Turn into constant?
  int sdl_image = IMG_Init(IMG_FLAGS);

  if (sdl_image != IMG_FLAGS) {
    printf("IMG Init Error: %s\n", SDL_GetError());
    exit(-1);
  }

  // SDL_mixer initialization
  int MIX_FLAGS = MIX_INIT_OGG; // TODO: Turn into constant?
  int sdl_mix = Mix_Init(MIX_FLAGS);

  if(sdl_mix != MIX_FLAGS) {
    printf("MIX Init Error: %s\n", SDL_GetError());
    exit(-1);
  }

  int DEFAULT_CHUNKSIZE = 1024;
  int mix_open = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                               MIX_DEFAULT_CHANNELS, DEFAULT_CHUNKSIZE);
  if (mix_open) {
    printf("Mix Open Audio: %s\n", SDL_GetError());
    exit(-1);
  }

  int CHANNELS = 32;
  int mix_channels = Mix_AllocateChannels(CHANNELS);
  if (mix_channels != CHANNELS) {
    printf("Mix Allocate Channels: %s\n", SDL_GetError());
    exit(-1);
  }

  if(TTF_Init()) {
    printf("TTF_Init: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
  }

  // Window creation
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (window == nullptr) {
    printf("SDL Create Window: %s\n", SDL_GetError());
    exit(-1);
  }
                               
  // Renderer creation
  int SUPPORTED_RENDERER = -1;
  renderer = SDL_CreateRenderer(window, SUPPORTED_RENDERER, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    printf("SDL Create Renderer: %s\n", SDL_GetError());
    exit(-1);
  }

  srand(time(NULL));

  this->storedState = nullptr;
}

Game::~Game() {
  if (this->storedState != nullptr)
    delete this->storedState;

  while(not this->stateStack.empty())
    this->stateStack.pop();

  Resources::Clear();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  Mix_Quit();
  Mix_CloseAudio();
  IMG_Quit();
  SDL_Quit();
}

void Game::Push(State *state) {
  this->storedState = state;
}

void Game::Run() {
  if (this->storedState != nullptr) {
    this->stateStack.emplace(this->storedState);
    this->GetCurrentState().Start();
    this->storedState = nullptr;
  }

  if (not this->stateStack.empty()) {
    this->CalculateDeltaTime(); // TODO: Where to put this?

    while (!this->GetCurrentState().QuitRequested() && !this->stateStack.empty()) {
      if (this->GetCurrentState().PopRequested()) {
        this->stateStack.pop();
        Resources::Clear();

        if (this->storedState != nullptr) {
          this->stateStack.emplace(this->storedState);
          this->GetCurrentState().Start();
          this->storedState = nullptr;
        }

        if (not this->stateStack.empty()) {
          this->GetCurrentState().Resume();
        } else {
          break;
        }
      }

      InputManager::GetInstance().Update();
      this->GetCurrentState().Update(this->GetDeltaTime());
      this->GetCurrentState().Render();
      SDL_RenderPresent(renderer);
      SDL_Delay(33); // TODO: Remove magic number (it is in milliseconds)
    }
  }
}

State& Game::GetCurrentState() {
  return *(this->stateStack.top());
}

SDL_Renderer* Game::GetRenderer() {
  return renderer;
}

Game &Game::GetInstance() {
  if (instance == nullptr)
    instance = new Game("Rage of the elders", 1024, 600);

  return *instance;
}

void Game::CalculateDeltaTime() {
  this->dt = SDL_GetTicks() - this->frameStart;
  this->frameStart += this->dt;
}

float Game::GetDeltaTime() {
	return this->dt/1000.0;
}