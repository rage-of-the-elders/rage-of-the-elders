#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "TileSet.h"
#include "TileMap.h"

#include <vector>
#include <memory>

class StageState : public State {
private:
  Music music;
  GameObject *bg;
  TileSet *tileSet;
  TileMap *tileMap;

  int stageLimit;

public:
  StageState();
  ~StageState();
  bool PlayerWon();
  bool PlayerLose();
  void Render();
  void Start();
  void Pause();
  void Resume();
  void LoadAssets();
  void LoadPlayers();
  void LoadEnemies();
  void CheckGameEnd();
  void BuildBarriers();
  void DeletionCheck();
  void Update(float dt);
  void CollisionCheck();
  void LoadBackground();
  void LockCamera(int tile);
};

#endif
