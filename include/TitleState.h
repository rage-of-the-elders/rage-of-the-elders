#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#define PLAY 0
#define DIFFICULTY 1
#define EXIT 2

#define SELECTED 0
#define CHANGE 1

#define OPTIONS_Y 480
#define OPTIONS_FONT "assets/font/Call me maybe.ttf"
#define OPTIONS_FONT_SIZE 55
#define SELECTED_OPTION LIGHT_GREEN
#define NOT_SELECTED_OPTION WHITE

#include <vector>
#include "State.h"
#include "Text.h"
#include "Sound.h"

class TitleState : public State {
private:
  int currentOption;
  std::vector<Text *> options;
  std::vector<Sound *> buttonSounds;

public:
  TitleState();
  ~TitleState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
};

#endif