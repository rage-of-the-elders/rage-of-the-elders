#include "State.h"

State::State() {
  quitRequested = false;
  bg = Sprite("img/ocean.jpg");
  music = Music("audio/stageState.ogg");
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