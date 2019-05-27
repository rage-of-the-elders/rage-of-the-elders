#ifndef VETERAN_H
#define VETERAN_H

#define VETERAN_HP 100
#define VETERAN_SPEED Vec2(10)

#include "Fighter.h"

class Veteran : public Fighter {
  private:
  void ManageInput(float dt);
  void UpdateStateMachine();

public:
  Veteran(GameObject &associated);
  ~Veteran();
  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
};

#endif