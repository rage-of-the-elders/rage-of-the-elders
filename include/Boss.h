#ifndef BOSS_H
#define BOSS_H

#define BOSS_HP 150
#define BOSS_SPEED 100
#define ATTACK_COOLDOWN 10
#define TEACHER_ULTIMATE_TIME 50

#include "Enemy.h"

class Boss : public Enemy {
protected:
  // Rect target;
  // Rect tagetPlayer;
  // void ManageInput(float dt);
  // void HandleMovement(float dt);
  // void HandleDying(float dt);
  // Timer attackCooldown;
  // int bossAttackCooldown;

public:
  Boss(GameObject &associated);
  ~Boss();
  void ResetSpeed();
  bool Is(std::string type);
  // void Start();
  // void ResetSpeed();
  // void Update(float dt);
  // void SetSpeed(int speed);
  // bool TargetIsInRange();
  // bool Is(std::string type);
  // void NotifyCollision(GameObject &other);
  // bool IsOpponent(GameObject &other);
};

#endif