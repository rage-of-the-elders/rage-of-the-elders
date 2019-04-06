#ifndef STATE_H
#define STATE_H

#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "Music.h"

#include <vector>
#include <memory>

class State {
private:
  Music music;
  bool quitRequested;
  std::vector<std::shared_ptr<GameObject>> objectArray;

  void Input();
  void AddObject(int mouseX, int mouseY);

public:
  State();
  ~State();
  bool QuitRequested();
  void LoadAssets();
  void Update(float dt);
  void Render();
};

#endif