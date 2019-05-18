#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "CameraFollower.h"

TitleState::TitleState() {
  GameObject *bg = new GameObject();
  bg->AddComponent(new Sprite(*bg, "img/title.jpg"));
  bg->AddComponent(new CameraFollower(*bg));
  this->AddObject(bg);

  this->LoadAssets();
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {
  GameObject *text = new GameObject();
  text->AddComponent(new Text(*text, "assets/font/Call me maybe.ttf", 65, Text::BLENDED,
                              "PRESS SPACE TO CONTINUE", WHITE, 2));
  text->AddComponent(new CameraFollower(*text, Vec2(512, 525) - (text->box.GetSize() / 2.0)));
  this->AddObject(text);
}

void TitleState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();

  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    this->quitRequested = true;

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    this->popRequested = true;
    Game::GetInstance().Push(new StageState());
  }

  this->UpdateArray(dt);
}

void TitleState::Render() {
  this->RenderArray();
}
void TitleState::Start() {
  this->StartArray();
  this->started = true;
}

void TitleState::Pause() {}
void TitleState::Resume() {}