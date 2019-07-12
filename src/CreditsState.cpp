#include "CreditsState.h"
#include "InputManager.h"
#include "TitleState.h"
#include "Game.h"

CreditsState::CreditsState() {
  this->changeScenes = Timer();
  this->fadeTimer = Timer();

  this->LoadAssets();
}

CreditsState::~CreditsState() {
  this->objectArray.clear();
}

void CreditsState::LoadAssets() {
  GameObject *bgGO = new GameObject();
  this->bg = new Sprite(*bgGO, "img/menu/credits-bg.png");
  bgGO->AddComponent(this->bg);
  this->AddObject(bgGO);

  this->names = new GameObject();
  this->fade = new Sprite(*names, "img/menu/credits.png");
  this->names->AddComponent(this->fade);
  this->names->box.SetXCenter(Game::screenWidth / 2);
  this->names->box.y = Game::screenHeight;

  this->music = new Music("audio/menu/credits.ogg");
  this->music->Play();

  this->AddObject(this->names);
}

void CreditsState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
   	Game::GetInstance().Push(new TitleState());
	}

  bool enterPressed = InputManager::GetInstance().KeyPress(ENTER_KEY) 
                      || InputManager::GetInstance().KeyPress(KEYPAD_ENTER_KEY)
                      || InputManager::GetInstance().KeyPress(SPACE_KEY);

  if (enterPressed)
    names->box.y -= CREDITS_SKIP;

  this->names->box.y -= CREDITS_SPEED;
  if (this->names->box.y < -(this->names->box.h + 10)) {
    this->popRequested = true;
    Game::GetInstance().Push(new TitleState(false));
  }

  this->UpdateArray(dt);
}

void CreditsState::Render() {
  this->RenderArray();
}

void CreditsState::Start() {
  this->StartArray();
  this->started = true;
}

void CreditsState::Pause() {}
void CreditsState::Resume() {}