#ifndef CHOOSE_PLAYER_STATE_H
#define CHOOSE_PLAYER_STATE_H

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Sound.h"

#define VETERAN_OPTION 0
#define TEACHER_OPTION 1


class ChoosePlayerState : public State {
private:
  int currentOption;
  Music music;
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
};

#endif
