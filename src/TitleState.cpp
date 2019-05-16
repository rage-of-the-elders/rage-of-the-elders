#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "CameraFollower.h"

TitleState::TitleState() {
  GameObject *go = new GameObject();
  go->AddComponent(new Sprite(*go, "img/title.jpg"));
  go->box = Rect();
  this->AddObject(go);

  go->AddComponent(new CameraFollower(*go));
}

TitleState::~TitleState() {}
void TitleState::LoadAssets() {}

void TitleState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();

  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    this->quitRequested = true;

  if (InputManager::GetInstance().KeyPress(SPACE_KEY))
    Game::GetInstance().Push(new StageState());

  this->UpdateArray(dt);
}

void TitleState::Render() {
  this->RenderArray();
}
void TitleState::Start() {
  this->StartArray();
}

void TitleState::Pause() {}
void TitleState::Resume() {}