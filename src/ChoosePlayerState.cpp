#include "ChoosePlayerState.h"
#include "InputManager.h"
#include "TitleState.h"
#include "StageState.h"
#include "Sprite.h"
#include "GameData.h"
#include "Game.h"

ChoosePlayerState::ChoosePlayerState() : State(){
  this->objectArray = std::vector<std::shared_ptr<GameObject>>();
  this->currentOption = 0;

  this->LoadAssets();
}

ChoosePlayerState::~ChoosePlayerState() {
}

void ChoosePlayerState::LoadAssets() {
  this->bg = new GameObject();
  this->bg->AddComponent(new Sprite(*bg, "img/menu/title-bright.png"));
  this->AddObject(bg);

  GameObject *sound = new GameObject();
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/select.ogg"));
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/cursor.ogg"));
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/cancel.ogg"));


  music = Music("audio/menu/bg.ogg");
  music.Play();
}

void ChoosePlayerState::Update(float dt) {
  printf("Curr opt: %d\n", currentOption);
  this->quitRequested = InputManager::GetInstance().QuitRequested();

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
   	Game::GetInstance().Push(new TitleState());
	}

  bool pressedLeft = InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)
                     || InputManager::GetInstance().KeyPress(A_KEY);
  bool pressedRight = InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)
                      || InputManager::GetInstance().KeyPress(D_KEY);
  bool enterPressed = InputManager::GetInstance().KeyPress(ENTER_KEY) 
                      || InputManager::GetInstance().KeyPress(KEYPAD_ENTER_KEY)
                      || InputManager::GetInstance().KeyPress(SPACE_KEY);

  if (pressedLeft && this->currentOption > VETERAN_OPTION) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentOption--;
  }

  if (pressedRight && this->currentOption < TEACHER_OPTION) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentOption++;
  }

  if (enterPressed) {
    this->buttonSounds[SELECTED]->Play(1);

    std::string character = "";
    switch (this->currentOption) {
      case VETERAN_OPTION:
        character = "veteran";
        break;

      case TEACHER_OPTION:
        character = "teacher";
        break;

      default:
        break;
    }
    this->popRequested = true;
    GameData::choosedCharacter = character;
    Game::GetInstance().Push(new StageState());
  }
  this->UpdateArray(dt);
}

void ChoosePlayerState::Render() {
  this->RenderArray();
}

void ChoosePlayerState::Start() {
  this->StartArray();
  this->started = true;
}

void ChoosePlayerState::Pause() {

}

void ChoosePlayerState::Resume() {

}
