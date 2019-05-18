#include "EndState.h"

#include "Game.h"
#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "CameraFollower.h"

EndState::EndState() {
  GameObject *bg = new GameObject();
  std::string bgImg = GameData::playerVictory ? "img/win.jpg" : "img/lose.jpg";
  bg->AddComponent(new Sprite(*bg, bgImg));
  bg->AddComponent(new CameraFollower(*bg));
  this->AddObject(bg);

  std::string audioFile = GameData::playerVictory ? "audio/endStateWin.ogg" : "audio/endStateLose.ogg";

  this->backgroundMusic = Music(audioFile);
  this->backgroundMusic.Play();

  this->LoadAssets();
}

EndState::~EndState() {
}

void EndState::LoadAssets() {
  GameObject *text = new GameObject();
  text->AddComponent(new Text(*text, "assets/font/Call me maybe.ttf", 70, Text::SOLID,
                              "PRESS SPACE TO CONTINUE", BLACK));
  text->AddComponent(new CameraFollower(*text, Vec2(512, 525) - (text->box.GetSize() / 2.0)));
  this->AddObject(text);

  GameObject *quitText = new GameObject();
  quitText->AddComponent(new Text(*quitText, "assets/font/Call me maybe.ttf", 70, Text::SOLID,
                                  "PRESS ESC TO CLOSE", BLACK));
  quitText->AddComponent(new CameraFollower(*quitText, Vec2(512, 25) - (quitText->box.GetSize() / 2.0)));
  this->AddObject(quitText);
}

void EndState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();

  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    this->quitRequested = true;

  if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
    this->popRequested = true;
    Game::GetInstance().Push(new StageState());
  }

  this->UpdateArray(dt);
}

void EndState::Render() {
  this->RenderArray();
}
void EndState::Start() {
  this->StartArray();
  this->started = true;
}

void EndState::Pause() {}
void EndState::Resume() {}