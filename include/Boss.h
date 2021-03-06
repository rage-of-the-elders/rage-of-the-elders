#ifndef BOSS_H
#define BOSS_H

#define BOSS_HP 500
#define BOSS_SPEED 400
#define ATTACK_COOLDOWN 10
#define TEACHER_ULTIMATE_TIME 50
#define HALF_OF_THE_SCREEN 640
#define WIDTH_OF_THE_SCREEN 1280
#define LEFT_GAP_TO_KEEP_BOSS_ON_THE_SCREEN 50
#define RIGHT_GAP_TO_KEEP_BOSS_ON_THE_SCREEN 400


#include "Enemy.h"

class Boss : public Enemy {
protected:
  void ManageInput(float dt);
  void HandleMovement(float dt);
  void HandleDying(float dt);
  bool bossIsOnLeft;
  bool bossAlredyMove;
  int timesThatTheBossTurnArround;
  Timer frozenTime;
  int turnArroundTimes;

public:
  Boss(GameObject &associated);
  ~Boss();
  void ResetSpeed();
  bool Is(std::string type);
  void Update(float dt);
};

#endif