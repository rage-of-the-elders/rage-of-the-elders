#ifndef VICTORY_STATE_H
#define VICTORY_STATE_H

#define SCENES_NUMBER 5
#define SCENE_DURATION 1.75 // seconds
#define FADE_DURATION 2 // seconds
#include "State.h"
#include "GameObject.h"
// #include "Music.h"
#include "Sprite.h"
#include "Sound.h"
#include "Timer.h"
// #include "Text.h"


class VictoryState : public State {
private:
  int currentScene;
  Sprite *cutscene;
  Sprite *fade;
  Timer changeScenes;
  Timer fadeTimer;
  std::vector<Sound *> buttonSounds;

public:
  VictoryState();
  ~VictoryState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
};

#endif
