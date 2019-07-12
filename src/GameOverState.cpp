#include "GameOverState.h"
#include "InputManager.h"
#include "TitleState.h"
#include "ChoosePlayerState.h"
#include "Game.h"

GameOverState::GameOverState() : State(){
  this->objectArray = std::vector<std::shared_ptr<GameObject>>();
  this->currentOption = 0;

  this->LoadAssets();
}

GameOverState::~GameOverState() {
}

void GameOverState::LoadAssets() {
  this->bg = new GameObject();
  this->bg->AddComponent(new Sprite(*bg, "img/menu/game-over.png", 12, 0.06));
  this->AddObject(bg);

  GameObject *go = new GameObject();
  this->options[BACK_TO_MENU_OPTION] = new Sprite(*go, "img/menu/back-to-menu.png");
  go->AddComponent(options[BACK_TO_MENU_OPTION]);
  go->box.SetCenterPos({Game::screenWidth/6, Game::screenHeight - 50});
  this->AddObject(go);

  go = new GameObject();
  this->options[PLAY_AGAIN_OPTION] = new Sprite(*go, "img/menu/play-again.png");
  go->AddComponent(options[PLAY_AGAIN_OPTION]);
  go->box.SetCenterPos({5*Game::screenWidth/6, Game::screenHeight - 50});
  this->AddObject(go);

  GameObject *sound = new GameObject();
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/select.ogg"));
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/cursor.ogg"));
  sound = new GameObject();
  this->buttonSounds.push_back(new Sound(*sound, "audio/menu/cancel.ogg"));

  this->music = new Music("audio/menu/credits.ogg");
  this->music->Play();
}

void GameOverState::Update(float dt) {
  this->HandleInput();
  this->UpdateScreenElements();
  this->UpdateArray(dt);
}

void GameOverState::Render() {
  this->RenderArray();
}


void GameOverState::Start() {
  this->StartArray();
  this->started = true;
}
void GameOverState::HandleInput() {
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

  if (pressedLeft && this->currentOption > BACK_TO_MENU_OPTION) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentOption--;
  }

  if (pressedRight && this->currentOption < PLAY_AGAIN_OPTION) {
    this->buttonSounds[CHANGE]->Play(1);
    this->currentOption++;
  }


  if (enterPressed) {
    this->buttonSounds[SELECTED]->Play(1);

    switch (this->currentOption) {
      case BACK_TO_MENU_OPTION:
        this->popRequested = true;
        Game::GetInstance().Push(new TitleState());
        break;

      case PLAY_AGAIN_OPTION:
        this->popRequested = true;
        Game::GetInstance().Push(new ChoosePlayerState());
        break;

      default:
        break;
    }
  }
}

void GameOverState::UpdateScreenElements() {
  int otherCharacter = this->currentOption == BACK_TO_MENU_OPTION ? PLAY_AGAIN_OPTION : BACK_TO_MENU_OPTION;

  this->options[currentOption]->SetScaleX(1.1);
  this->options[otherCharacter]->SetScaleX(0.75);
}

void GameOverState::Pause() {

}

void GameOverState::Resume() {

}
