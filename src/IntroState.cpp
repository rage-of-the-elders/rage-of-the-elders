#include "IntroState.h"
#include "InputManager.h"
#include "ChoosePlayerState.h"
#include "StageState.h"
#include "Game.h"

IntroState::IntroState() {
  this->changeScenes = Timer();
  this->fadeTimer = Timer();
  this->currentScene = 0;

  this->LoadAssets();
}

IntroState::~IntroState() {
  this->objectArray.clear();
}

void IntroState::LoadAssets() {
  GameObject *bgGO = new GameObject();
  this->bg = new Sprite(*bgGO, "img/cutscenes/typewriter.jpeg");
  bgGO->AddComponent(this->bg);
  this->AddObject(bgGO);

  GameObject *fadeGO = new GameObject();
  this->fade = new Sprite(*fadeGO, "img/black.png");
  fadeGO->AddComponent(this->fade);
  this->AddObject(fadeGO);
  fade->SetAlpha(100);

  this->music = new Music("audio/menu/credits.ogg");
  this->music->Play();
}

void IntroState::UpdateFade(float dt) {
  float fadeCompletionPercentage = fadeTimer.Get() / FADE_DURATION;
  this->fadeTimer.Update(dt);
  this->fade->SetAlpha(floor(fadeCompletionPercentage * 100), true);
  // this->bg->SetScaleX(bg->GetScale().x+dt);
}

void IntroState::UpdateCutscene(float dt) {
  #ifdef DEBUG
    if (InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)) {
      // this->cutscene->SetFrame(++currentScene);
    }
    if (InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)) {
      // this->cutscene->SetFrame(--currentScene);
    }
  #endif

  // if (changeScenes.Get() > TEXT_DURATION) {
  //   if(this->currentScene < LINES_NUMBER) {
  //     this->bg->SetFrame(++currentScene);
  //   } else {
  //     this->popRequested = true;
  //     Game::GetInstance().Push(new CreditsState());
  //   }
  //   changeScenes.Restart();
  // }
  this->changeScenes.Update(dt);
}

void IntroState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
   	Game::GetInstance().Push(new ChoosePlayerState());
	}
  if (InputManager::GetInstance().KeyPress(ENTER_KEY)) {
		this->popRequested = true;
   	Game::GetInstance().Push(new StageState());
	}

  if (fadeTimer.Get() < FADE_DURATION) {
    this->UpdateFade(dt);
  } else {
    // this->UpdateCutscene(dt);
  }

  this->UpdateArray(dt);
}

void IntroState::Render() {
  this->RenderArray();
}

void IntroState::Start() {
  this->StartArray();
  this->started = true;
}

void IntroState::Pause() {}
void IntroState::Resume() {}