#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_HP 100
#define ENEMY_SPEED 10
#define ATTACK_Y_RANGE 15

#include "Fighter.h"

class Enemy : public Fighter {
private:
  Rect target;
  void ManageInput(float dt);
  void HandleMovement(float dt);
  void HandleDying(float dt);

public:
  Enemy(GameObject &associated);
  ~Enemy();
  void Start();
  bool TargetIsInRange();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
  bool IsOpponent(GameObject &other);
};

#endif