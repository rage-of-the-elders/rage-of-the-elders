#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include <memory>

class State {
private:
  Sprite bg;
  Music music;
  bool quitRequested;
  std::vector<std::unique_ptr<GameObject>> objectArray;

  void Input();
  void AddObject(int mouseX, int mouseY);

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Input();
};

#endif