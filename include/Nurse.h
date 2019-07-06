#ifndef NURSE_H
#define NURSE_H

#define NURSE_ATTACK_COOLDOWN 5

#include "Enemy.h"

class Nurse : public Enemy {
// private:
//   Rect target;
//   void ManageInput(float dt);
//   void HandleMovement(float dt);
//   void HandleDying(float dt);

public:
  Nurse(GameObject &associated);
  ~Nurse();
  void ResetSpeed();
  void Update(float dt);
  bool Is(std::string type);
  // void Start();
  // bool TargetIsInRange();
  // bool Is(std::string type);
  // void NotifyCollision(GameObject &other);
  // bool IsOpponent(GameObject &other);
};

#endif