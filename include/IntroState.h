#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#define TEXT_DURATION 2 // seconds
#define LINES_NUMBER 2 // seconds
#define FADE_DURATION 2 // seconds
#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Timer.h"


class IntroState : public State {
private:
  int currentScene;
  Sprite *bg;
  Sprite *fade;
  // GameObject *names;
  Music *music;
  Timer changeScenes;
  Timer fadeTimer;

public:
  IntroState();
  ~IntroState();
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
