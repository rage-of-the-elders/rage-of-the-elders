#ifndef CHOOSE_PLAYER_STATE_H
#define CHOOSE_PLAYER_STATE_H

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Sound.h"
#include "Text.h"

#define VETERAN_OPTION 0
#define TEACHER_OPTION 1


class ChoosePlayerState : public State {
private:
  int currentCharacter;
  Music music;
  Sprite *characters[2];
  Sprite *characterNames[2];
  GameObject *bg;
  std::vector<Sound *> buttonSounds;

public:
  ChoosePlayerState();
  ~ChoosePlayerState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
  void HandleInput();
  void UpdateScreenElements();
};

#endif
