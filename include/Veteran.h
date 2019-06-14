#ifndef VETERAN_H
#define VETERAN_H

#define VETERAN_HP 100
#define VETERAN_SPEED 50

#include "Fighter.h"

class Veteran : public Fighter {
private:
  void ManageInput(float dt);
  void UpdateStateMachine(float dt);

public:
  static Veteran *player;
  Veteran(GameObject &associated);
  ~Veteran();
  void Start();
  bool Is(std::string type);
  bool IsOpponent(GameObject &other);
  void NotifyCollision(GameObject &other);
};

#endif