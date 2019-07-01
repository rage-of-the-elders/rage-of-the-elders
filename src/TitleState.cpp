#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "CameraFollower.h"

TitleState::TitleState() {
  this->currentOption = 0;
  GameObject *bg = new GameObject();
  bg->AddComponent(new Sprite(*bg, "img/title.png"));
  bg->AddComponent(new CameraFollower(*bg));
  this->AddObject(bg);

  this->LoadAssets();
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {
  GameObject *text = new GameObject();
  this->options.push_back(new Text(*text, OPTIONS_FONT, OPTIONS_FONT_SIZE, Text::BLENDED, "PLAY", WHITE, 0.5));
  text = new GameObject();
  this->options.push_back(new Text(*text, OPTIONS_FONT, OPTIONS_FONT_SIZE, Text::BLENDED, "DIFFICULTY", WHITE, 0.5));
  text = new GameObject();
  this->options.push_back(new Text(*text, OPTIONS_FONT, OPTIONS_FONT_SIZE, Text::BLENDED, "EXIT", WHITE, 0.5));

  currentOption = 1;
  this->options[currentOption]->SetPos(640, OPTIONS_Y);

  // positioning options before current option
  for(int i = 0; i < currentOption; i++){
  	Text* nextOption = options[i + 1];

    int newX = nextOption->GetBox().x - options[i]->GetBox().w - 20;
    options[i]->SetPos(newX, OPTIONS_Y, false, true);
    options[i]->SetColor(NOT_SELECTED_OPTION);
  }

  // positioning options after current option
  for(unsigned int i = currentOption + 1; i < options.size(); i++){
  	Text* previousOption = options[i - 1];

    int newX = previousOption->GetBox().x + previousOption->GetBox().w + 20;
    options[i]->SetPos(newX, OPTIONS_Y, false, true);
  	options[i]->SetColor(NOT_SELECTED_OPTION);
  }
  currentOption = 0;

  GameObject *sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*text, "audio/select.ogg"));
  this->buttonSounds.push_back(new Sound(*text, "audio/cursor.ogg"));
}

void TitleState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();

  bool pressedLeft = InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY) || InputManager::GetInstance().KeyPress(A_KEY);
  bool pressedRight = InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY) || InputManager::GetInstance().KeyPress(D_KEY);

  if (pressedLeft && this->currentOption > 0) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentOption--;
  }

  if (pressedRight && this->currentOption < this->options.size() - 1) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentOption++;
  }

  for(auto &option : this->options) {
    option->SetColor(NOT_SELECTED_OPTION);
  }
  this->options[currentOption]->SetColor(SELECTED_OPTION);


  if (InputManager::GetInstance().KeyPress(ENTER_KEY) || InputManager::GetInstance().KeyPress(KEYPAD_ENTER_KEY)) {
    this->buttonSounds[SELECTED]->Play(1);
    switch (this->currentOption) {
      case PLAY:
        this->popRequested = true;
        Game::GetInstance().Push(new StageState());
        break;

      case DIFFICULTY:
        break;

      case EXIT:
        this->quitRequested = true;
        break;
      default:
        break;
    }
  }

  this->UpdateArray(dt);
}

void TitleState::Render() {
  this->RenderArray();

  for (auto option : this->options) {
    option->Render();
  }
}
void TitleState::Start() {
  this->StartArray();
  this->started = true;
}

void TitleState::Pause() {}
void TitleState::Resume() {}