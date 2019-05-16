#ifndef STATE_STATE_H
#define STATE_STATE_H

#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "TileSet.h"

#include <vector>
#include <memory>

class StageState : public State {
private:
  Music music;
  TileSet *tileSet;
  GameObject *bg;
  GameObject *mapGameObj;

public:
  StageState();
  ~StageState();
  void LoadAssets();
  void Update(float dt);
  void Render();
  void Start();
  void Pause();
  void Resume();
};

#endif