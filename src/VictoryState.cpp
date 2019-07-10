#include "VictoryState.h"
#include "InputManager.h"
#include "TitleState.h"
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
}

void VictoryState::Update(float dt) {
  this->quitRequested = InputManager::GetInstance().QuitRequested();
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		this->popRequested = true;
   	Game::GetInstance().Push(new TitleState());
	}

  if (fadeTimer.Get() < FADE_DURATION) {
    float fadeCompletionPercentage = fadeTimer.Get()/FADE_DURATION;
    printf("complete: %f\n", fadeCompletionPercentage * 100);
    this->fadeTimer.Update(dt);
    this->fade->SetAlpha(floor(fadeCompletionPercentage * 100), true);
  } else {
    if (changeScenes.Get() > SCENE_DURATION) {
      if(this->currentScene < SCENES_NUMBER) {
        this->cutscene->SetFrame(++currentScene);
      } else {
        // cutscene->SetAlpha();
        this->popRequested = true;
        Game::GetInstance().Push(new TitleState(false)); // TODO: Change to Credits
      }
      changeScenes.Restart();
    }
    this->changeScenes.Update(dt);
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