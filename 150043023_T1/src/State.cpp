#include "State.h"
#include "Game.h"

State::State() : bg("img/ocean.jpg"), music("audio/stageState.ogg") {
  quitRequested = false;
}

void State::LoadAssets() {
  // TODO
}

void State::Update(float dt) {
  if (SDL_QuitRequested()) {
    quitRequested = true;
  }
}

void State::Render() {
  bg.Render(0, 0);
}

bool State::QuitRequested() {
  return quitRequested;
}