#ifndef JANITOR_H
#define JANITOR_H

#include "Enemy.h"

class Janitor : public Enemy {
// private:
//   Rect target;
//   void ManageInput(float dt);
//   void HandleMovement(float dt);
//   void HandleDying(float dt);

public:
  Janitor(GameObject &associated);
  ~Janitor();
  // void Start();
  // bool TargetIsInRange();
  // bool Is(std::string type);
  // void NotifyCollision(GameObject &other);
  // bool IsOpponent(GameObject &other);
};

#endif