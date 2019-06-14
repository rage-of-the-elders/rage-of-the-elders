#ifndef NURSE_H
#define NURSE_H

#define NURSE_HP 100
#define NURSE_SPEED 10
#define ATTACK_Y_RANGE 15

#include "Fighter.h"

class Nurse : public Fighter {
private:
  Rect target;
  void ManageInput(float dt);
  void HandleMovement(float dt);
  void HandleDying(float dt);

public:
  Nurse(GameObject &associated);
  ~Nurse();
  void Start();
  bool TargetIsInRange();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
  bool IsOpponent(GameObject &other);
};

#endif