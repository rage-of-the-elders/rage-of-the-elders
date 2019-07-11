#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include "State.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "TileSet.h"
#include "TileMap.h"
#include "GateMap.h"
#include "ObjectMap.h"

#include <vector>
#include <memory>

class StageState : public State {
private:
  Music music;
  GameObject *bg;
  TileSet *tileSet;
  TileMap *tileMap;
  GateMap *gateMap;
  ObjectMap *objectMap;
  GameObject *cameraLockWallLeft;
  GameObject *cameraLockWallRight;

  bool hordeEnabled;

  int stageLimit;
  static int enemiesCount;

public:
  StageState();
  ~StageState();

  bool PlayerWon();
  bool PlayerLose();

  int CalculateEnemyY(Vec2 enemySize, int yLimit);

  void Start();
  void Pause();
  void Render();
  void Resume();
  void LoadGates();
  void LoadAssets();
  void LoadPlayers();
  void HandleHorde();
  void UnlockCamera();
  void CheckGameEnd();
  void BuildBarriers();
  void DeletionCheck();
  void Update(float dt);
  void CollisionCheck();
  void LoadBackground();
  void LoadSceneObjects();
  void LockCamera(int gatePosition);
  void SpawnEnemies(int gatePosition, Gate gate);

  static void DecreaseEnemiesCount();

  /*
    If you want the enemy to come from the left side of the screen, set the value
    of "invertSide" as zero. Otherwise, set the attribute to a non-zero value.

    yLimit defines the limit where a enemy can be rendered. Default is 500px
    (Usualy, this is near the base of the wall)
  */

  void Spawn(int xPosition, int type, int invertSide, int yLimit = 500);
};

#endif
