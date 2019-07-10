#include "ChoosePlayerState.h"
#include "InputManager.h"
#include "TitleState.h"
#include "StageState.h"
#include "Sprite.h"
#include "GameData.h"
#include "Game.h"

ChoosePlayerState::ChoosePlayerState() : State(){
  this->objectArray = std::vector<std::shared_ptr<GameObject>>();
  this->currentCharacter = 0;

  this->LoadAssets();
}

ChoosePlayerState::~ChoosePlayerState() {
}

void ChoosePlayerState::LoadAssets() {
  this->bg = new GameObject();
  this->bg->AddComponent(new Sprite(*bg, "img/menu/choose-player.png"));
  this->AddObject(bg);

  float leftXPosition = (Game::screenWidth/2) - 205;
  float rightXPosition = (Game::screenWidth/2) + 265;
  float yPosition = Game::screenHeight / 2;

  auto go = new GameObject();
  this->characters[VETERAN_OPTION] = new Sprite(*go, "img/veteran/idle.png", 15, STOP_SPRITE);
  go->AddComponent(characters[VETERAN_OPTION]);
  go->box.SetCenterPos(leftXPosition, yPosition + 30);
  this->AddObject(go);

  go = new GameObject();
  this->characters[TEACHER_OPTION] = new Sprite(*go, "img/teacher/idle.png", 25, STOP_SPRITE);
  go->AddComponent(characters[TEACHER_OPTION]);
  go->box.SetCenterPos(rightXPosition, yPosition);
  this->AddObject(go);

  auto text = new GameObject();
  text->AddComponent(new Sprite(*text, "img/menu/choose-your-player.png"));
  text->box.SetCenterPos(Game::screenWidth/2, 70);
  this->AddObject(text);

  text = new GameObject();
  this->characterNames[VETERAN_OPTION] = new Sprite(*text, "img/menu/veteran.png");
  text->AddComponent(characterNames[VETERAN_OPTION]);
  text->box.SetCenterPos(leftXPosition, yPosition + 262);
  this->AddObject(text);

  text = new GameObject();
  this->characterNames[TEACHER_OPTION] = new Sprite(*text, "img/menu/teacher.png");
  text->AddComponent(characterNames[TEACHER_OPTION]);
  text->box.SetCenterPos(rightXPosition, yPosition + 235);
  this->AddObject(text);
  
  GameObject *sound = new GameObject();
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/select.ogg"));
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/cursor.ogg"));
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/cancel.ogg"));
}

void ChoosePlayerState::Update(float dt) {
  this->HandleInput();
  this->UpdateScreenElements();
  this->UpdateArray(dt);
}

void ChoosePlayerState::Render() {
  this->RenderArray();
}


void ChoosePlayerState::Start() {
  this->StartArray();
  this->started = true;
}
void ChoosePlayerState::HandleInput() {
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

  if (pressedLeft && this->currentCharacter > VETERAN_OPTION) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentCharacter--;
  }

  if (pressedRight && this->currentCharacter < TEACHER_OPTION) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentCharacter++;
  }


  if (enterPressed) {
    this->buttonSounds[SELECTED]->Play(1);

    std::string character = "";
    switch (this->currentCharacter) {
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
}

void ChoosePlayerState::UpdateScreenElements() {
  int otherCharacter = currentCharacter == VETERAN_OPTION ? TEACHER_OPTION : VETERAN_OPTION;
  this->characters[currentCharacter]->SetFrameTime(0.04);
  this->characters[otherCharacter]->SetFrameTime(STOP_SPRITE);

  this->characterNames[currentCharacter]->SetScaleX(0.7);
  this->characterNames[otherCharacter]->SetScaleX(0.5);
}
void ChoosePlayerState::Pause() {

}

void ChoosePlayerState::Resume() {

}
