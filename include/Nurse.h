#ifndef NURSE_H
#define NURSE_H

#define NURSE_HP 100
#define NURSE_SPEED 20

#include "Fighter.h"

class Nurse : public Fighter {
private:
  Vec2 target;
  void UpdateStateMachine();

public:
  Nurse(GameObject &associated);
  ~Nurse();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
};

#endif