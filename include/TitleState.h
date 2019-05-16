#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "State.h"
// #include "GameObject.h"
// #include "Sprite.h"
// #include "Sound.h"
// #include "Music.h"
// #include "TileSet.h"

// #include <vector>
// #include <memory>

class TitleState : public State {
private:

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