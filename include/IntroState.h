#ifndef INTRO_STATE_H
#define INTRO_STATE_H

#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "Sprite.h"
#include "Timer.h"

#define TYPEWRITER_SPEED 0.35 // seconds
#define INTRO_TEXT_SPEED 1.8 // seconds
#define FADE_DURATION 2 // seconds
#define TEXT_POS Vec2(570, 115)

class IntroState : public State {
private:
  int currentScene;
  Sprite *bg;
  Sprite *fade;
  Sprite *names;
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
