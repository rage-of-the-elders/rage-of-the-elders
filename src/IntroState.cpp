#include "IntroState.h"
#include "InputManager.h"
#include "ChoosePlayerState.h"
#include "StageState.h"
#include "GameData.h"
#include "Game.h"

IntroState::IntroState() {
  this->fadeTimer = Timer();
  this->currentScene = 0;

  this->LoadAssets();
}

IntroState::~IntroState() {
  this->typewriter->Stop();
  this->objectArray.clear();
}

void IntroState::LoadAssets() {
  GameObject *bgGO = new GameObject();
  this->bg = new Sprite(*bgGO, "img/cutscenes/typewriter.png", 5, TYPEWRITER_SPEED);
  bgGO->AddComponent(this->bg);
  this->AddObject(bgGO);

  int frameNumber = 0;
  if (GameData::choosedCharacter == "veteran") {
    frameNumber = 32;
  } else {
    frameNumber = 34;
  }

  GameObject *textGO = new GameObject();
  this->names = new Sprite(*textGO,
                           "img/cutscenes/" + GameData::choosedCharacter + "-text.png",
                           frameNumber,
                           INTRO_TEXT_SPEED,
                           0,
                           false);
  names->Desactivate();
  textGO->box.SetCenterPos(TEXT_POS);
  textGO->angleDeg = 90;
  textGO->AddComponent(this->names);
  this->AddObject(textGO);

  GameObject *fadeGO = new GameObject();
  this->fade = new Sprite(*fadeGO, "img/black.png");
  fadeGO->AddComponent(this->fade);
  this->AddObject(fadeGO);
  fade->SetAlpha(100);

  this->music = new Music("audio/menu/credits.ogg");
  this->music->Play();

  GameObject *typewriterGO = new GameObject();
  this->typewriter = new Sound(*typewriterGO, "audio/menu/typewriter.ogg");
  this->AddObject(typewriterGO);
  typewriter->Play();
}

void IntroState::UpdateFade(float dt) {
  float fadeCompletionPercentage = fadeTimer.Get() / FADE_DURATION;
  this->fadeTimer.Update(dt);
  this->fade->SetAlpha(floor(fadeCompletionPercentage * 100), true);
}

void IntroState::UpdateScreenElements(float dt) {
  if (fadeTimer.Get() < FADE_DURATION) {
    this->UpdateFade(dt);
  } else {
    bool enterPressed = InputManager::GetInstance().KeyPress(ENTER_KEY)
                        || InputManager::GetInstance().KeyPress(KEYPAD_ENTER_KEY)
                        || InputManager::GetInstance().KeyPress(SPACE_KEY);

    if (enterPressed) {
      this->names->SetFrame(std::min(this->names->GetFrameCount()-1 , this->names->GetFrame() + 1));
    }

    if(not this->names->IsActive()) {
      this->names->Activate();
    }

    if(this->names->IsFinished()) {
      this->popRequested = true;
      Game::GetInstance().Push(new StageState());
    }
  }
}

void IntroState::Update(float dt) {
  #ifdef DEBUG
    if (InputManager::GetInstance().KeyPress(M_KEY)) {
      this->popRequested = true;
      Game::GetInstance().Push(new StageState());
    }
  #endif

  this->quitRequested = InputManager::GetInstance().QuitRequested();
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
   	Game::GetInstance().Push(new ChoosePlayerState());
	}

  this->UpdateScreenElements(dt);
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
