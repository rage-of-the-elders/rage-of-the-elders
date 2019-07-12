#include "VictoryState.h"
#include "InputManager.h"
#include "TitleState.h"
#include "CreditsState.h"
#include "Game.h"

VictoryState::VictoryState() {
  this->changeScenes = Timer();
  this->fadeTimer = Timer();
  this->currentScene = 0;

  this->LoadAssets();
}

VictoryState::~VictoryState() {
  this->objectArray.clear();
}

void VictoryState::LoadAssets() {
  GameObject *cutsceneGO = new GameObject();
  this->cutscene = new Sprite(*cutsceneGO, "img/cutscenes/endgame.png", SCENES_NUMBER, STOP_SPRITE);
  cutsceneGO->AddComponent(this->cutscene);
  this->AddObject(cutsceneGO);

  GameObject *fadeGO = new GameObject();
  this->fade = new Sprite(*fadeGO, "img/black.png");
  fadeGO->AddComponent(this->fade);
  this->AddObject(fadeGO);
  fade->SetAlpha(0);

  this->music = new Music("audio/menu/victory.ogg");
  this->music->Play();
}

void VictoryState::UpdateFade(float dt) {
  float fadeCompletionPercentage = fadeTimer.Get() / FADE_DURATION;
  this->fadeTimer.Update(dt);
  this->fade->SetAlpha(floor(fadeCompletionPercentage * 100), true);
}

void VictoryState::UpdateCutscene(float dt) {
  #ifdef DEBUG
    if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)) {
      this->cutscene->SetFrame(++currentScene);
    }
    if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)) {
      this->cutscene->SetFrame(--currentScene);
    }
  #endif

  if (changeScenes.Get() > SCENE_DURATION) {
    if(this->currentScene < SCENES_NUMBER) {
      this->cutscene->SetFrame(++currentScene);
    } else {
      this->popRequested = true;
      Game::GetInstance().Push(new CreditsState());
    }
    changeScenes.Restart();
  }
  this->changeScenes.Update(dt);
}

void VictoryState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();

  if (fadeTimer.Get() < FADE_DURATION) {
    this->UpdateFade(dt);
  } else {
    this->UpdateCutscene(dt);
  }

  this->UpdateArray(dt);
}

void VictoryState::Render() {
  this->RenderArray();
}

void VictoryState::Start() {
  this->StartArray();
  this->started = true;
}

void VictoryState::Pause() {}
void VictoryState::Resume() {}