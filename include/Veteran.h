#ifndef VETERAN_H
#define VETERAN_H

#define VETERAN_HP 100
#define VETERAN_SPEED 50

#include "Fighter.h"

class Veteran : public Fighter {
  private:
  void ManageInput(float dt);
  void UpdateStateMachine();

public:
  static Veteran *player;
  Veteran(GameObject &associated);
  ~Veteran();
  void Start();
  void Update(float dt);
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
};

#endif
