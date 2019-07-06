#ifndef SECURITY_H
#define SECURITY_H

#define SECURITY_ATTACK_COOLDOWN 2

#include "Enemy.h"

class Security : public Enemy {
private:
//   Rect target;
//   void ManageInput(float dt);
//   void HandleMovement(float dt);
  void HandleDying(float dt);

public:
  Security(GameObject &associated);
  ~Security();
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