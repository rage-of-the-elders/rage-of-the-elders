#include "State.h"

State::State() {
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
  // TODO
}

bool State::QuitRequested() {
  return quitRequested;
}