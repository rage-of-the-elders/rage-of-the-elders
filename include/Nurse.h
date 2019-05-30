#ifndef NURSE_H
#define NURSE_H

#define NURSE_HP 100
#define NURSE_SPEED 10
#define ATTACK_Y_RANGE 50

#include "Fighter.h"

class Nurse : public Fighter {
private:
  Rect target;
  void UpdateStateMachine();

public:
  Nurse(GameObject &associated);
  ~Nurse();
  void Start();
  void Update(float dt);
  bool TargetIsInRange();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
};

#endif