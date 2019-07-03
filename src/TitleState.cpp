#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "CameraFollower.h"
#include "Camera.h"

TitleState::TitleState(bool startOption) {
  this->currentOption = 0;
  this->startPressed = startOption;
  this->flickerTimer = Timer();
  this->showText = false;

  this->LoadAssets();
}

TitleState::~TitleState() {}

void TitleState::LoadAssets() {
  this->bgBright = new GameObject();
  this->bgBright->AddComponent(new Sprite(*bgBright, "img/menu/title-bright.png"));
  this->AddObject(bgBright);

  this->gameName = new GameObject();
  Sprite *name = new Sprite(*gameName, "img/menu/name-2.png", 15, 0.15);
  name->SetScaleX(0.8);
  this->gameName->AddComponent(name);
  this->gameName->box.SetPos(650, 10);
  this->AddObject(gameName);

  this->bgDark = new GameObject();
  Sprite *black = new Sprite(*bgDark, "img/black.png");
  black->SetAlpha(160);
  this->bgDark->AddComponent(black);
  this->AddObject(bgDark);


  if (not this->startPressed)
    bgDark->Desactivate();

  GameObject *text = new GameObject();
  this->startOption = new Text(*text, OPTIONS_FONT, OPTIONS_FONT_SIZE, Text::BLENDED, "PRESS START", WHITE, 0.5);
  this->startOption->SetPos(640, OPTIONS_Y);
  Camera::Follow(text);
  text = new GameObject();
  this->options.push_back(new Text(*text, OPTIONS_FONT, OPTIONS_FONT_SIZE, Text::BLENDED, "PLAY", WHITE));
  text = new GameObject();
  this->options.push_back(new Text(*text, OPTIONS_FONT, OPTIONS_FONT_SIZE, Text::BLENDED, "DIFFICULTY", WHITE));
  text = new GameObject();
  this->options.push_back(new Text(*text, OPTIONS_FONT, OPTIONS_FONT_SIZE, Text::BLENDED, "EXIT", WHITE));

  currentOption = 1;
  this->options[currentOption]->SetPos(640, OPTIONS_Y);

  // positioning options before current option
  for(int i = 0; i < currentOption; i++){
  	Text* nextOption = options[i + 1];

    int newX = nextOption->GetBox().x - options[i]->GetBox().w - OPTIONS_SPACING;
    options[i]->SetPos(newX, OPTIONS_Y, false, true);
    options[i]->SetColor(NOT_SELECTED_OPTION);
  }

  // positioning options after current option
  for(unsigned int i = currentOption + 1; i < options.size(); i++){
  	Text* previousOption = options[i - 1];

    int newX = previousOption->GetBox().x + previousOption->GetBox().w + OPTIONS_SPACING;
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

    if(this->startPressed) {
      if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        this->buttonSounds[SELECTED]->Play(1);
        this->startPressed = false;
        this->bgDark->Desactivate();
        // this->bgBright->Activate();
      }

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
    } else {
      flickerTimer.Update(dt);
      if (flickerTimer.Get() > TEXT_FLICKER_TIME) {
        this->showText = not this->showText;
        flickerTimer.Restart();
      }
    }

    if (InputManager::GetInstance().KeyPress(ENTER_KEY) || InputManager::GetInstance().KeyPress(KEYPAD_ENTER_KEY)) {  
      this->buttonSounds[SELECTED]->Play(1);

      if (not startPressed) {
        this->currentOption = PLAY;
        this->startPressed = true;
        // this->bgBright->Desactivate();
        this->bgDark->Activate();
        // bg = new GameObject();
        // bg->AddComponent(new Sprite(*bg, "img/title.png"));
        // bg->AddComponent(new CameraFollower(*bg));
        // this->AddObject(bg);
        // this->bg->RemoveComponent("Sprite");
        // this->bg->AddComponent(new Sprite(*bg, "img/title.png"));
      } else {
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
    }

  this->UpdateArray(dt);
}

void TitleState::Render() {
  this->RenderArray();

  if (startPressed) {
    for (auto option : this->options) {
      option->Render();
    }
  } else {
    if (this->showText) {
      this->startOption->Render();
    }
  }
}
void TitleState::Start() {
  this->StartArray();
  this->started = true;
}

void TitleState::Pause() {}
void TitleState::Resume() {}