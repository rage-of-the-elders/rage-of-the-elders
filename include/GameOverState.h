#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#define BACK_TO_MENU_OPTION 0
#define PLAY_AGAIN_OPTION 1

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Sound.h"


class GameOverState : public State {
private:
  int currentOption;
  Music *music;
  GameObject *bg;
  Sprite *options[2];
  std::vector<Sound *> buttonSounds;

public:
  GameOverState();
  ~GameOverState();
  void LoadAssets();
  void HandleInput();
  void Update(float dt);
  void UpdateScreenElements();
  void Render();
  void Start();
  void Pause();
  void Resume();
};

#endif
