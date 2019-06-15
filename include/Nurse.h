#ifndef NURSE_H
#define NURSE_H

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
  // void Start();
  // bool TargetIsInRange();
  // bool Is(std::string type);
  // void NotifyCollision(GameObject &other);
  // bool IsOpponent(GameObject &other);
};

#endif