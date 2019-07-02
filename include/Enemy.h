#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_HP 100
#define ENEMY_SPEED 100
#define ATTACK_COOLDOWN 10
#define TEACHER_ULTIMATE_TIME 50

#include "Fighter.h"

class Enemy : public Fighter {
protected:
  Rect target;
  Rect tagetPlayer;
  void ManageInput(float dt);
  void HandleMovement(float dt);
  void HandleDying(float dt);
  Timer attackCooldown;
  float enemyAttackCooldown;

public:
  Enemy(GameObject &associated);
  ~Enemy();
  void Start();
  void ResetSpeed();
  void Update(float dt);
  void SetSpeed(int speed);
  bool TargetIsInRange();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
  bool IsOpponent(GameObject &other);
};

#endif