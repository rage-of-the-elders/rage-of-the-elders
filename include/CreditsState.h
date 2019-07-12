#ifndef CREDITS_STATE_H
#define CREDITS_STATE_H

#define FADE_DURATION 2 // seconds
#define CREDITS_SPEED 4
#define CREDITS_SKIP 300
#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Sound.h"
#include "Timer.h"


class CreditsState : public State {
private:
  Sprite *bg;
  Sprite *fade;
  GameObject *names;
  Music *music;
  Timer changeScenes;
  Timer fadeTimer;
  std::vector<Sound *> buttonSounds;

public:
  CreditsState();
  ~CreditsState();
  void LoadAssets();
  void Update(float dt);
  void UpdateFade(float dt);
  void UpdateCutscene(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
};

#endif
