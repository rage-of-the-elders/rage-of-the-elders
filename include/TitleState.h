#ifndef TITLE_STATE_H
#define TITLE_STATE_H


#define PLAY 0
#define DIFFICULTY 1
#define EXIT 2

#define SELECTED 0
#define CHANGE 1

#define TEXT_FLICKER_TIME 0.35
#define OPTIONS_Y 480
#define OPTIONS_FONT "assets/font/Berlin Sans FB Demi Negrito.ttf"
#define OPTIONS_FONT_SIZE 50
#define SELECTED_OPTION YELLOW
#define NOT_SELECTED_OPTION WHITE

#include <vector>
#include "State.h"
#include "Text.h"
#include "Sound.h"

class TitleState : public State {
private:
  int currentOption;
  bool startPressed;
  bool showText;
  std::vector<Text *> options;
  std::vector<Sound *> buttonSounds;
  Text *startOption;
  GameObject *bgBright;
  GameObject *bgDark;
  Timer flickerTimer;

public:
  TitleState(bool startOption = true);
  ~TitleState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
};

#endif